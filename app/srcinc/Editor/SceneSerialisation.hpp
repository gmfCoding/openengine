#ifndef OE_SCENE_SERIALISATION_HPP
#define OE_SCENE_SERIALISATION_HPP

#include "Core/Scene.hpp"
#include <map>
#include <vector>
#include <nlohmann/json.hpp>

/// @brief Scene Serialisation Class for editor
class SceneSerialisation
{
    std::map<EntityID, std::vector<char>> entityToUUIDs;
    std::map<std::vector<char>, EntityID> UUIDtoEntitys;

    public:
    SceneSerialisation();

    void Save(Scene& scene);
    void SaveHierarchy(nlohmann::ordered_json& json, Scene& scene, EntityHierarchyNode* node);
    void SaveEntity(nlohmann::ordered_json& ejc, Scene& scene, Entity entity);
    void Load(const std::string& name);


    std::vector<char> GetUUID(EntityID id);
    EntityID GetEntityID(std::vector<char> uuid);
};
#endif