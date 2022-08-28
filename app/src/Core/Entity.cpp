#include "Entity.hpp"
#include "Systems/Scenes.hpp"

Entity Entity::none = Entity {EntityID(0), SceneID(0)};

std::string Entity::GetName()
{
    return GetScene()->GetEntityName(*this);
}


void Entity::SetName(std::string name)
{
    GetScene()->SetEntityName(*this, name);
}

template<typename T>
Component* Entity::GetComponent()
{
    return GetScene()->GetComponent<T>(id);
}

template<typename T>
std::vector<Component*> Entity::GetComponents()
{
    return GetScene()->GetComponents<T>(id);
}


template<typename T>
T* Entity::AddComponent()
{
    return GetScene()->AddComponent<T>(id);
}


Component* Entity::AddComponent(CompID cid)
{
    return GetScene()->AddComponent(*this, cid);
}


template<typename T>
void Entity::RemoveComponent()
{
    return GetScene()->RemoveComponent<T>(id);
}


bool Entity::Exists()
{
    return id > 0 && scene > 0;
}

std::vector<Component*> Entity::GetAllComponents()
{
    return GetScene()->GetAllComponents(*this);
}


Entity Entity::GetParent()
{
    auto p = GetScene()->entityHierarchyMap[this->id]->m_parent;
    return Entity { p ? p->m_id : 0, scene};
}

void Entity::SetParent(Entity entity, int index)
{
    GetScene()->SetParent(entity, *this, index);
}


void Entity::SetIndex(int i)
{
    GetScene()->SetEntityIndex(*this, i);
}


Scene* Entity::GetScene()
{
    return Scenes::Get(scene);
}




