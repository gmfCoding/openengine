#ifndef OE_SCENE_H
#define OE_SCENE_H
#include <concepts>

#ifdef OE_SRC_USE_PCH
#include "pch/pch.hpp"
#else
#include <string>
#include <vector>
#include <unordered_set>
#include <set>
#include <unordered_map>
#endif

#include <list>

#include "Core/Types.hpp"

#include "Systems/InstanceSystem.hpp"

#include "Entity.hpp"


class Component;
class ActiveComponent;

namespace std {
    template<> 
    struct hash<Entity>
    {
        std::size_t operator()(const Entity& pointToHash) const noexcept 
        {
            size_t hash = pointToHash.id;
            return hash;
        };
    };
}

class EntityHierarchyNode
{
    public:
    std::set<EntityHierarchyNode*> m_nodes;
    EntityHierarchyNode* m_parent;
    EntityID m_id;

    EntityHierarchyNode(EntityID id, EntityHierarchyNode* parent) : m_id(id), m_parent(parent)
    {

    }

};

class Scene
{
    SceneID sceneID;

    std::unordered_map<EntityID, std::vector<Component*>> entityComponents;
    std::unordered_set<ActiveComponent*> activeComponents;

    public:
    std::set<EntityHierarchyNode*> root;
    std::unordered_map<EntityID, EntityHierarchyNode*> entityHierarchyMap;

    std::unordered_set<Entity> entities;  

    static InstanceSet<EntityID> entityIDs;

    static std::unordered_map<EntityID, std::string> entityNames;



public:

    Scene();
    
    std::string GetEntityName(Entity entity);

    void SetEntityName(Entity entity, std::string& name);

    template<typename T>
    T* GetComponent(Entity entity);

    template<typename T>
    std::vector<T*> GetComponents(Entity entity);

    std::vector<Component*> GetAllComponents(Entity entity);

    template<typename T>
    T* AddComponent(Entity entity);

    Component* AddComponent(Entity entity, CompID cid);

    template<typename T>
    void RemoveComponent(Entity entity);
    template<typename T>
    void RemoveComponent(Entity entity, Component* component);
    
    template <typename T>
    std::enable_if_t<std::is_base_of<Component, T>::value, T*> GetComponent(Entity entity);

    bool IsEntityAssigned(Entity entity);

    Entity CreateEntity();
    Entity CreateEntity(std::string name);
    Entity CreateEntity(std::string name, Entity parent);
    Entity CreateEntity(Entity parent);

    void SetParent(Entity parentEtre, Entity childEtre);

    void AddEntity(Entity entity);
    void AddEntity(Entity entity, std::vector<Component*> components);
    static void MoveEntity(Entity entity, SceneID dest);
    void RemoveEntity(Entity entity);
    void DeleteEntity(Entity entity);


    SceneID GetSceneID();


    friend class Scenes;
};
#endif