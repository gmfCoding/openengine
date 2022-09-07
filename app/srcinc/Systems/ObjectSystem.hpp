#ifndef OE_OBJECTSYSTEM_HPP
#define OE_OBJECTSYSTEM_HPP

#include "Core/ObjectReference.hpp"
#include "Systems/InstanceSystem.hpp"

#ifdef OE_SRC_USE_PCH
#include "pch/pch.hpp"
#else
#include <unordered_map>
#include <vector>
#endif

class ObjectSystem
{
    static ObjectSystem instance;

    InstanceSet<CommonID> identities;

    std::unordered_map<CommonID, char[]> idToUUID;
    std::unordered_map<CommonID, void*> objects;

    template<typename T>
    T* m_GetObject(ObjectReference<T> ref);

    template<typename T>
    static T* GetObject(ObjectReference<T> ref);



    CommonID m_NewID();
    static CommonID NewID();


    CommonID m_Save(void* data);
    static CommonID Save(void* data);
};
#endif