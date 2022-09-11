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
#include <iostream>
#endif

#include <list>

#include "Core/Types.hpp"

#include "Systems/InstanceSystem.hpp"

#include "Entity.hpp"

#include "Core/ObjectReference.hpp"
#include "Systems/ObjectSystem.hpp"



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
    std::vector<EntityHierarchyNode*> m_nodes;
    EntityHierarchyNode* m_parent;
    EntityID m_id;

    EntityHierarchyNode(EntityID id, EntityHierarchyNode* parent) : m_id(id), m_parent(parent)
    {

    }

    
    ~EntityHierarchyNode()
    {
        std::cout << "Deleting Entity:" << m_id;
    }
};

enum DeletionOrigin
{
    DeleteHierarchy,
    DeleteEntity,
    External
};

class Scene
{
    SceneID sceneID;

    ObjectSystem system;

    std::unordered_map<EntityID, std::vector<CommonID>> entityComponents;
    std::unordered_set<CommonID> activeComponents;

    public:
    std::vector<EntityHierarchyNode*> root;
    std::unordered_map<EntityID, EntityHierarchyNode*> entityHierarchyMap;

    std::unordered_set<Entity> entities;

    static std::unordered_map<EntityID, std::string> entityNames;

public:

    Scene();
    
    std::string GetEntityName(Entity entity);

    void SetEntityName(Entity entity, std::string& name);

    template<typename T>
    ObjectReference<T> GetComponent(Entity entity);

    template<typename T>
    std::vector<ObjectReference<T>> GetComponents(Entity entity);

    std::vector<CommonID> GetAllComponents(Entity entity);

    template<typename T>
    ObjectReference<T> AddComponent(Entity entity);

    ObjectReference<Component> AddComponent(Entity entity, CompID cid);

    template<typename T>
    void RemoveComponent(Entity entity);
    template<typename T>
    void RemoveComponent(Entity entity, Component* component);
    
    template <typename T>
    std::enable_if_t<std::is_base_of<Component, T>::value, ObjectReference<T>> GetComponent(Entity entity);

    bool IsEntityAssigned(Entity entity);

    Entity CreateEntity();
    Entity CreateEntity(std::string name);
    Entity CreateEntity(std::string name, Entity parent);
    Entity CreateEntity(Entity parent);

    void SetParent(Entity parentEtre, Entity childEtre, int index = 0);
    void SetEntityIndex(Entity entity, int index);

    void AddEntity(Entity entity);
    
    static void MoveEntity(Entity entity, SceneID dest);

    void RemoveEntity(Entity entity);
    void DeleteEntity(Entity entity, DeletionOrigin delctx = DeletionOrigin::External);
    void EraseEntityHierarchy(EntityHierarchyNode* n);
    void DeleteEntityFromHierarchy(Entity entity);
    void DeleteHierarchy(EntityHierarchyNode* e, DeletionOrigin delctx = DeletionOrigin::External);
    
    std::vector<EntityHierarchyNode*>* GetParentVector(EntityHierarchyNode* e);

    SceneID GetSceneID();

    friend class SceneSerialisation;
    friend class Scenes;
};
#endif