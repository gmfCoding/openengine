#include "format.h"
#include "Core/Scene.hpp"
#include "Systems/Scenes.hpp"
#include "Core/Types.hpp"
#include "Components/Component.hpp"


InstanceSet<EntityID> Scene::entityIDs;
std::unordered_map<EntityID, std::string> Scene::entityNames;

Scene::Scene() : entityComponents(), activeComponents(), root(), entities()
{

}


std::string Scene::GetEntityName(Entity entity)
{
    if(IsEntityAssigned(entity) && entityNames.count(entity.id))
        return entityNames[entity.id];
    return "Unnamed Entity!";
}


void Scene::SetEntityName(Entity entity, std::string& name)
{
    entityNames[entity.id] = name;
}

template<typename T>
T* Scene::GetComponent(Entity entity)
{
    if(IsEntityAssigned(entity) && entityComponents.count(entity.id))
    {
        for (auto i : entityComponents[entity.id])
        {
            if(i->CID == T::CID)
            {
                return i;
            }
        }
    }

    return nullptr;
}

template<typename T>
std::vector<T*> Scene::GetComponents(Entity entity)
{
    std::vector<T*> comps = std::vector<T*>();
    if(IsEntityAssigned(entity) && entityComponents.count(entity.id))
    {
        for (auto i : entityComponents[entity.id])
        {
            if(i->CID == T::CID)
            {
                comps.push_back((T*)i);
            }
        }
    }

    return comps;
}


std::vector<Component*> Scene::GetAllComponents(Entity entity)
{
    if(IsEntityAssigned(entity) && entityComponents.count(entity.id))
    {
        return entityComponents[entity.id];
    }

    return std::vector<Component*>(0);
}

template<typename T>
T* Scene::AddComponent(Entity entity)
{
    if(IsEntityAssigned(entity))
    {
        T* comp = new T();
        entityComponents[entity.id].push_back(comp);
        if(comp->IsActiveComponent())
            activeComponents.emplace((ActiveComponent*)comp);
        return comp;
    }
    return nullptr;
}


template<typename T>
void Scene::RemoveComponent(Entity entity)
{
    if(IsEntityAssigned(entity) && entityComponents.count(entity.id))
    {
        for(auto it = entityComponents[entity.id].begin(); it != entityComponents[entity.id].end(); ++it) {
            if((*it)->m_instanceID == T::CID)
            {
                entityComponents[entity.id].erase(it);
                break;
            }
        }
    }
}

template<typename T>
void Scene::RemoveComponent(Entity entity, Component* component)
{
    if(IsEntityAssigned(entity) && entityComponents.count(entity.id))
    {
        for(auto it = entityComponents[entity.id].begin(); it != entityComponents[entity.id].end(); ++it) {
            if((*it) == component)
            {
                entityComponents[entity.id].erase(it);
                break;
            }
        }
    }
}

template <typename T>
std::enable_if_t<std::is_base_of<Component, T>::value, T*> Scene::GetComponent(Entity entity)
{
    if(IsEntityAssigned(entity) && entities.count(entity))
    {
        for (auto &&i : entityComponents[entity.id])
        {
            if(i->m_ComponentType == T::CID)
                return i;
        }
    }
}




void Scene::AddEntity(Entity entity)
{
    if(entity.scene != sceneID)
    {
        Scene* old = Scenes::Get(entity.scene);
        entity.scene = sceneID;
        if(old)
        {
            // Grap all the Components from the old Scene
            std::vector<Component*> components = old->GetAllComponents(entity);
            // Emplace all the ActiveComponents
            for(auto it = components.begin(); it != components.end(); ++it) {
                if((*it)->IsActiveComponent())
                {
                    activeComponents.emplace((ActiveComponent*)(*it));
                }
            }
            old->RemoveEntity(entity);
        }
    }
}

void Scene::AddEntity(Entity entity, std::vector<Component*> components)
{
    if(IsEntityAssigned(entity))
    {
        Scene* old = Scenes::Get(entity.scene);
        if(old)
            old->RemoveEntity(entity);

        entity.scene = sceneID;
        this->entityComponents[entity.id] = components;

        // Emplace all the ActiveComponents
        for(auto it = components.begin(); it != components.end(); ++it) {
            if((*it)->IsActiveComponent())
            {
                activeComponents.emplace((ActiveComponent*)(*it));
            }
        }

    }
}

void Scene::MoveEntity(Entity entity, SceneID dest)
{
    Scene* _old = Scenes::Get(entity.scene);
    Scene* _new = Scenes::Get(dest);

    if(!_new)
    {
        //TODO: Use a proper logging method
        //assert(oestd::format("Cannot move entity:%u - %s in %u to %u",entity.id, _old->GetEntityName(entity), dest));
        return;
    }

    if(_old)
    {
        std::vector<Component*> components = _old->GetAllComponents(entity);
        _old->RemoveEntity(entity);
        _new->AddEntity(entity);
    }
    else
    {
        //TODO: WARNING entity does not exist in any scenes cannot move to a new scene
        return;
    }

}

void Scene::RemoveEntity(Entity entity)
{
    if(IsEntityAssigned(entity) && entityComponents.count(entity.id))
    {
        // Remove all ActiveComponents
        for(auto it = entityComponents[entity.id].begin(); it != entityComponents[entity.id].end(); ++it) {
            if((*it)->IsActiveComponent())
            {
                activeComponents.erase((ActiveComponent*)(*it));
            }
        }

        entityComponents.erase(entity.id);
    }
}

void Scene::DeleteEntity(Entity entity)
{
    if(IsEntityAssigned(entity))
    {
        // Remove all ActiveComponents
        for(auto it = entityComponents[entity.id].begin(); it != entityComponents[entity.id].end(); ++it) {
            auto test = *it;
            if(test->IsActiveComponent())
            {
                activeComponents.erase((ActiveComponent*)(*it));
            }
        }

        entityComponents.erase(entity.id);
    }
}

Entity Scene::CreateEntity()
{
    Entity e = Entity();
    e.id = entityIDs.GetNew();
    e.scene = sceneID;
    entities.emplace(e);
    auto ehn = new EntityHierarchyNode(e.id, nullptr);
    root.emplace(ehn);
    entityHierarchyMap.emplace(e.id, ehn);
    return e;
}

Entity Scene::CreateEntity(std::string name) 
{
    Entity e = CreateEntity();
    SetEntityName(e, name);
}

Entity Scene::CreateEntity(std::string name, Entity parent)
{
    Entity e = CreateEntity(name);
    SetParent(parent, e);
}

Entity Scene::CreateEntity(Entity parent)
{
    Entity e = CreateEntity();
    SetParent(parent, e);
    return e;
}

/**
 *  @brief True if supplied entity is in this scene
 *  @param entity
 */
bool Scene::IsEntityAssigned(Entity entity)
{
    return entity.scene == sceneID;
}

void Scene::SetParent(Entity parentEtre, Entity childEtre)
{
    if(parentEtre.scene == childEtre.scene)
    {
        auto c = entityHierarchyMap[childEtre.id];
        auto p = entityHierarchyMap[parentEtre.id];
        if(c->m_parent)
            c->m_parent->m_nodes.erase(c);
        else
            this->root.erase(c);
        c->m_parent = p;
        c->m_parent->m_nodes.emplace(c);
    }
    //TODO: WARNING "Cannot set parent as it is in a different scene"
}

SceneID Scene::GetSceneID()
{
    return sceneID;
}