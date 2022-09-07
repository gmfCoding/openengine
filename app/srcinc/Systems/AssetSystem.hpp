#ifndef OE_ASSETSYSTEM_HPP
#define OE_ASSETSYSTEM_HPP

#include "Core/ObjectReference.hpp"
#include "Systems/InstanceSystem.hpp"

#ifdef OE_SRC_USE_PCH
#include "pch/pch.hpp"
#else
#include <unordered_map>
#include <vector>
#include <string>
#endif

class AssetSystem
{
    static AssetSystem instance;

    std::unordered_map<CommonID, char*> idToUUID;
    std::unordered_map<char*, std::string> fileLocations;

    AssetSystem()
    {

    }

    template<typename T>
    T* m_GetObject(ObjectReference<T> ref);

    template<typename T>
    static T* GetObject(ObjectReference<T> ref);
};
#endif
