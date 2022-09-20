#include "Editor/SceneSerialisation.hpp"
#include <nlohmann/json.hpp>
#include "Util/uuidgen.hpp"

#include <iostream>
#include <fstream>

#include "Components/Component.hpp"
#include "Core/ObjectReference.hpp"
#include "Core/Object.hpp"

SceneSerialisation::SceneSerialisation() : entityToUUIDs(), UUIDtoEntitys()
{
    
}

void SceneSerialisation::Save(Scene& scene)
{
    nlohmann::ordered_json json;
    json["type"] = "scene";
    json["id"] = scene.sceneID;
    
    for (auto i : scene.root)
    {
        SaveHierarchy(json["entities"], scene, i);
    }
    
    // write prettified JSON to another file
    std::ofstream output("pretty.json");
    output << std::setw(4) << json << std::endl;
}


void SceneSerialisation::SaveHierarchy(nlohmann::ordered_json& ejc, Scene& scene, EntityHierarchyNode* node)
{
    Entity entity = {node->m_id, scene.sceneID};
    std::vector<char> uuid = SceneSerialisation::GetUUID(entity.id);
    SaveEntity(ejc[&uuid[0]], scene, entity);
    for (auto i : node->m_nodes)
    {
        SaveHierarchy(ejc[&uuid[0]]["children"], scene, i);
    }
}


void SceneSerialisation::SaveEntity(nlohmann::ordered_json& ejc, Scene& scene, Entity entity)
{
    auto& entjson = ejc;
    entjson["name"] = entity.GetName();
    auto& components = entjson["components"];
    for (auto &&i : scene.GetComponents<Component>(entity))
    {
        std::vector<char> c_uuid = SceneSerialisation::GetUUID(i.m_id);
        auto& comp = components[&c_uuid[0]];
        comp["type"] = i.Get()->m_ComponentType;
        std::vector<SObject*> properties;
        i.Get()->GetPropertiesLocal(properties);
        auto& compdata =  comp["data"];

        // For each properties list (each class has it's own, even base/super classes)
        for(auto p : properties)
        {
            bool first = true;
            // For each properties in ^^each list
            for(auto p2 : p->properties)
            {
                // Skip the first because it is the component name
                if (first)
                { first = false; continue; }
                std::string type = p2.second.type;
                auto& prop = compdata[p2.first];
                void* value = p2.second.GetPtr(i.Get());
                if(type == "int")
                    prop = {type, *(int*)value};
                else if(type == "float")
                    prop = {type, *(float*)value};
                else if(type == "std::string")
                    prop = {type, *(std::string*)value};
                else if(type == "bool")
                    prop = {type, *(bool*)value};
                else if(type.find("ObjectReference") != std::string::npos)
                {
                    ObjectReference<void> object = *(ObjectReference<void>*)value;
                    std::vector<char> or_uuid = SceneSerialisation::GetUUID(object.m_id);
                    prop = {type, &or_uuid[0]};
                }
            }
        }
    }
}

void SceneSerialisation::Load(const std::string& name)
{


}


std::vector<char> SceneSerialisation::GetUUID(EntityID id)
{
    std::vector<char> vec(37);
    if(this->entityToUUIDs.count(id) == 0)
    {
        UUIDGen::create_guid(vec.data());
        vec.push_back('\0');
        entityToUUIDs.emplace(id, vec);
    }

    return entityToUUIDs[id];
}

EntityID SceneSerialisation::GetEntityID(std::vector<char> uuid)
{
    return 0;
}