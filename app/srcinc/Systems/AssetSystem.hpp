#ifndef OE_ASSETSYSTEM_HPP
#define OE_ASSETSYSTEM_HPP

#include "Systems/InstanceSystem.hpp"
#include "Core/ObjectLocation.hpp"

#ifdef OE_SRC_USE_PCH
#include "pch/pch.hpp"
#else
#include <unordered_map>
#include <vector>
#include <string>
#endif


template<typename T>
class ObjectReference;

class AssetSystem
{
    static AssetSystem instance;

    std::unordered_map<CommonID, char*> idToUUID;
    std::unordered_map<char*, std::string> fileLocations;
    public:
    AssetSystem()
    {

    }


    template<typename T>
    T* m_GetObject(ObjectReference<T> ref);

    template<typename T>
    static T* GetObject(ObjectReference<T> ref);
};
#endif

#ifndef SKIP_OE_ASSET_SYSTEM
#ifndef OE_ASSETSYSTEM_TEMPLATE_IMPL
#define OE_ASSETSYSTEM_TEMPALTE_IMPL
template<typename T>
T* AssetSystem::m_GetObject(ObjectReference<T> ref)
{
    return nullptr;
}

template<typename T>
T* AssetSystem::GetObject(ObjectReference<T> ref)
{
    return nullptr;
}
#endif
#endif