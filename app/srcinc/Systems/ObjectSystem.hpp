#ifndef OE_OBJECTSYSTEM_HPP
#define OE_OBJECTSYSTEM_HPP

#include "Systems/InstanceSystem.hpp"
#include "Core/ObjectLocation.hpp"
#include "AssetSystem.hpp"

#ifdef OE_SRC_USE_PCH
#include "pch/pch.hpp"
#else
#include <unordered_map>
#include <vector>
#endif

template<typename T>
class ObjectReference;

class ObjectSystem
{
    public:
    static ObjectSystem instance;

    InstanceSet<CommonID> identities;

    std::unordered_map<CommonID, char[]> idToUUID;
    std::unordered_map<CommonID, void*> objects;

    template<typename T>
    T* m_GetObject(const ObjectReference<T>& ref);

    template<typename T>
    static T* GetObject(const ObjectReference<T>& ref);

    CommonID m_NewID();
    static CommonID NewID();


    CommonID m_Save(void* data);
    static CommonID Save(void* data);
};
#endif


#ifndef OE_OBJECT_SYSTEM_TEMPLATE_IMPL
#define OE_OBJECT_SYSTEM_TEMPLATE_IMPL
template<typename T>
T* ObjectSystem::m_GetObject(const ObjectReference<T>& ref)
{
    if(ref.m_location == ObjectLocation::SCENE)
    {
        return (T*)this->objects[ref.m_id];
    }

    return AssetSystem::GetObject(ref);
}

template<typename T>
T* ObjectSystem::GetObject(const ObjectReference<T>& ref)
{
    return ObjectSystem::instance.m_GetObject(ref);
}
#endif