#include <algorithm>

#include "format.h"
#include "Core/Scene.hpp"
#include "Systems/Scenes.hpp"
#include "Core/Types.hpp"
#include "Components/Component.hpp"

std::unordered_map<EntityID, std::string> Scene::entityNames;

Scene::Scene() : entityComponents(), activeComponents(), root(), entities()
{
}

std::string Scene::GetEntityName(Entity entity)
{
    if (IsEntityAssigned(entity) && entityNames.count(entity.id))
        return entityNames[entity.id];
    return "Unnamed Entity!";
}

void Scene::SetEntityName(Entity entity, std::string &name)
{
    entityNames[entity.id] = name;
}

template <typename T>
ObjectReference<T> Scene::GetComponent(Entity entity)
{
    if (IsEntityAssigned(entity) && entityComponents.count(entity.id))
    {
        for (auto i : entityComponents[entity.id])
        {
            ObjectReference<T> ref = {i, ObjectLocation::SCENE};
            if (ref->CID == T::CID)
            {
                return ref;
            }
        }
    }

    return nullptr;
}

std::vector<CommonID> Scene::GetAllComponents(Entity entity)
{
    if (IsEntityAssigned(entity) && entityComponents.count(entity.id))
    {
        return entityComponents[entity.id];
    }

    return std::vector<CommonID>(0);
}

template <typename T>
ObjectReference<T> Scene::AddComponent(Entity entity)
{
    return this->AddComponent(entity, T::CID);
}

ObjectReference<Component> Scene::AddComponent(Entity entity, CompID cid)
{
    if (IsEntityAssigned(entity))
    {
        Component* comp = Component::instantiate(cid);
        CommonID id = comp->m_instanceID;
        ObjectReference<Component> ref(id);

        componentToEntity.emplace(id, entity.id);
        entityComponents[entity.id].push_back(id);
        if (ref->IsActiveComponent())
            activeComponents.emplace(id);
        return ref;
    }
    return ObjectReference<Component>(0);
}

template <typename T>
std::enable_if_t<std::is_base_of<Component, T>::value, ObjectReference<T>> Scene::GetComponent(Entity entity)
{
    if (IsEntityAssigned(entity) && entities.count(entity))
    {
        for (auto &&i : entityComponents[entity.id])
        {
            ObjectReference<Component> ref(i);
            if (ref->m_ComponentType == T::CID)
                return ref;
        }
    }

    return ObjectReference<Component>(0);
}

template <typename T>
void Scene::RemoveComponent(Entity entity)
{
    if (IsEntityAssigned(entity) && entityComponents.count(entity.id))
    {
        for (auto it = entityComponents[entity.id].begin(); it != entityComponents[entity.id].end(); ++it)
        {
            if ((ObjectReference<Component>(*it))->m_instanceID == T::CID)
            {
                componentToEntity.erase((ObjectReference<Component>(*it))->m_instanceID);
                entityComponents[entity.id].erase(it);
                break;
            }
        }
    }
}

template <typename T>
void Scene::RemoveComponent(Entity entity, Component *component)
{

    if (IsEntityAssigned(entity) && entityComponents.count(entity.id))
    {
        for (auto it = entityComponents[entity.id].begin(); it != entityComponents[entity.id].end(); ++it)
        {
            if ((ObjectReference<Component>(*it).Get()) == component)
            {
                componentToEntity.erase((ObjectReference<Component>(*it))->m_instanceID);
                entityComponents[entity.id].erase(it);
                break;
            }
        }
    }
}

EntityID Scene::GetEntityFromComponentInstance(CommonID component)
{
    if(componentToEntity.count(component) > 0)
        return componentToEntity[component];
    return 0;
}

/*
* Adds an entity in this scene.
*/
void Scene::AddEntity(Entity entity)
{
    if (entity.scene != sceneID)
    {
        Scene *old = Scenes::Get(entity.scene);
        entity.scene = sceneID;
        if (old)
        {
            // Grap all the Components from the old Scene
            std::vector<CommonID> components = old->GetAllComponents(entity);
            // Emplace all the ActiveComponents
            for (auto it = components.begin(); it != components.end(); ++it)
            {
                if ((ObjectReference<Component>(*it)->IsActiveComponent()))
                {
                    activeComponents.emplace(*it);
                }
            }
            old->RemoveEntity(entity);
        }
    }
}

/*
* Moves an entity to a different scene.
*/
void Scene::MoveEntity(Entity entity, SceneID dest)
{
    Scene *_old = Scenes::Get(entity.scene);
    Scene *_new = Scenes::Get(dest);

    if (!_new)
    {
        // TODO: Use a proper logging method
        // assert(oestd::format("Cannot move entity:%u - %s in %u to %u",entity.id, _old->GetEntityName(entity), dest));
        return;
    }

    if (_old)
    {
        std::vector<CommonID> components = _old->GetAllComponents(entity);
        _old->RemoveEntity(entity);
        _new->AddEntity(entity);
    }
    else
    {
        // TODO: WARNING entity does not exist in any scenes cannot move to a new scene
        return;
    }
}

/*
* Remove all components from an entity.
*/
void Scene::RemoveEntity(Entity entity)
{
    if (IsEntityAssigned(entity) && entityComponents.count(entity.id))
    {
        // Remove all ActiveComponents
        for (auto it = entityComponents[entity.id].begin(); it != entityComponents[entity.id].end(); ++it)
        {
            if ((ObjectReference<Component>(*it))->IsActiveComponent())
            {
                activeComponents.erase(*it);
            }
        }

        entityComponents.erase(entity.id);
    }
}

/*
* Deletes an entity from scene.
* delctx should almost always be defaulted to external, it controls some logic flow and if set incorrectly an infinite loop could occure.
*/
void Scene::DeleteEntity(Entity entity, DeletionOrigin delctx)
{
    if (IsEntityAssigned(entity))
    {
        // Remove all ActiveComponents
        for (auto it = entityComponents[entity.id].begin(); it != entityComponents[entity.id].end(); ++it)
        {
            if (ObjectReference<Component>(*it)->IsActiveComponent())
            {
                activeComponents.erase(*it);
            }
        }

        entityComponents.erase(entity.id);

        // Don't delete the hierarchy as this function was called from DeleteHeirarchy which would deal with the children.
        if(delctx != DeletionOrigin::DeleteHierarchy)
        {
            auto node = entityHierarchyMap[entity.id];
            DeleteHierarchy(node, DeletionOrigin::DeleteEntity);
        }
    }
}


/*
* Erases the node n from scene hierarchy.
* Prefer use of DeleteEntityFromHierarchy
* Use DeleteHierarchy or DeleteEntity to correctly remove from scene.
*/
void Scene::EraseEntityHierarchy(EntityHierarchyNode* n)
{
    auto &pn = *GetParentVector(n);
    pn.erase(std::find(pn.begin(), pn.end(), n));
    entityHierarchyMap.erase(n->m_id);
    delete n;
}

/*
* Erases the Entity n from scene hierarchy.
* Use DeleteHierarchy or DeleteEntity to correctly remove from scene.
*/
void Scene::DeleteEntityFromHierarchy(Entity entity)
{
    if(!IsEntityAssigned(entity))
        return;
    auto n = entityHierarchyMap[entity.id];
    EraseEntityHierarchy(n);
}


/*
* Deletes node n's entity from scene.
* delctx should almost always be defaulted to external, it controls some logic flow and if set incorrectly an infinite loop could occure.
*/
void Scene::DeleteHierarchy(EntityHierarchyNode* e, DeletionOrigin delctx)
{
    // Skip DeleteEntity if this is being called from there, so we don't cause an infinite loop.
    if(delctx != DeletionOrigin::DeleteEntity)
        DeleteEntity(Entity {e->m_id, sceneID}, DeletionOrigin::DeleteHierarchy);

    for (auto i : e->m_nodes)
    {
        DeleteHierarchy(i, DeletionOrigin::DeleteHierarchy);
    }

    DeleteEntityFromHierarchy(Entity {e->m_id, sceneID});
}



/*
* Creates an entity in this scene.
*/
Entity Scene::CreateEntity()
{
    Entity* a = new Entity();
    Entity& e = *a;
    e.id = system.Save(a);
    e.scene = sceneID;
    entities.emplace(e);
    auto ehn = new EntityHierarchyNode(e.id, nullptr);
    root.push_back(ehn);
    entityHierarchyMap.emplace(e.id, ehn);
    return e;
}

/*
* Creates an entity in this scene with a name.
*/
Entity Scene::CreateEntity(std::string name)
{
    Entity e = CreateEntity();
    SetEntityName(e, name);
    return e;
}


/*
* Creates an entity in this scene with a name and parent.
*/
Entity Scene::CreateEntity(std::string name, Entity parent)
{
    Entity e = CreateEntity(name);
    SetParent(parent, e);
    return e;
}

/*
* Creates an entity in this scene with a parent.
*/
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

void Scene::SetParent(Entity parentEtre, Entity childEtre, int index)
{
    if (parentEtre.scene == childEtre.scene)
    {
        auto c = entityHierarchyMap[childEtre.id];
        auto p = entityHierarchyMap[parentEtre.id];

        if (parentEtre.id == 0 && c->m_parent)
        {
            c->m_parent->m_nodes.erase(std::find(c->m_parent->m_nodes.begin(), c->m_parent->m_nodes.end(), c));
            this->root.push_back(c);
        }
        else if (c->m_parent != p)
        {
            if (c->m_parent)
                c->m_parent->m_nodes.erase(std::find(c->m_parent->m_nodes.begin(), c->m_parent->m_nodes.end(), c));
            else
                this->root.erase(std::find(this->root.begin(), this->root.end(), c));
            c->m_parent = p;
            p->m_nodes.push_back(c);
        }

        if (index >= 0)
            SetEntityIndex(childEtre, index);
    }
    // TODO: WARNING "Cannot set parent as it is in a different scene"
}

template <typename t>
void move(std::vector<t> &v, size_t oldIndex, size_t newIndex)
{
    if (oldIndex > newIndex)
        std::rotate(v.rend() - oldIndex - 1, v.rend() - oldIndex, v.rend() - newIndex);
    else
        std::rotate(v.begin() + oldIndex, v.begin() + oldIndex + 1, v.begin() + newIndex + 1);
}

void Scene::SetEntityIndex(Entity entity, int index)
{
    auto c = entityHierarchyMap[entity.id];

    auto pn = *GetParentVector(c);

    auto fnd = std::find(pn.begin(), pn.end(), c);

    if (index < 0)
        index = 0;
    if (index >= pn.size())
        index = pn.size() - 1;

    move(pn, std::distance(pn.begin(), fnd), index);
}


std::vector<EntityHierarchyNode*>* Scene::GetParentVector(EntityHierarchyNode* e)
{
    auto pn = &(this->root);
    if(e->m_parent)
        pn = &(e->m_parent->m_nodes);
    return pn;
}

SceneID Scene::GetSceneID()
{
    return sceneID;
}