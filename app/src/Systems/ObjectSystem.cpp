#include "Systems/ObjectSystem.hpp"
#define SKIP_OE_ASSET_SYSTEM
#include "Systems/AssetSystem.hpp"
#undef SKIP_OE_ASSET_SYSTEM
ObjectSystem ObjectSystem::instance;

CommonID ObjectSystem::m_NewID()
{
    return identities.GetNew();
}

CommonID ObjectSystem::NewID()
{
    return ObjectSystem::instance.m_NewID();
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
