#include "Systems/AssetSystem.hpp"

AssetSystem AssetSystem::instance;

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