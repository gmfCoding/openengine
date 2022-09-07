#include "Systems/ObjectSystem.hpp"
#include "Systems/AssetSystem.hpp"

ObjectSystem ObjectSystem::instance;

template<typename T>
T* ObjectSystem::m_GetObject(ObjectReference<T> ref)
{
    if(ref.location == ObjectLocation::SCENE)
    {
        return (T*)this->objects[ref.id];
    }

    return AssetSystem::GetObject(ref);
}

template<typename T>
T* ObjectSystem::GetObject(ObjectReference<T> ref)
{
    return ObjectSystem::instance.m_GetObject(ref);
}


CommonID ObjectSystem::m_NewID()
{
    return identities.GetNew();
}

CommonID ObjectSystem::NewID()
{
    return ObjectSystem::instance.NewID();
}

CommonID ObjectSystem::m_Save(void* data)
{
    CommonID id = this->NewID();
    objects[id] = data;
    return id;
}

CommonID ObjectSystem::Save(void* data)
{
    return ObjectSystem::instance.m_Save(data);
}
