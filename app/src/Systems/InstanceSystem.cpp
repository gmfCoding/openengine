#include "Systems/InstanceSystem.hpp"

#include <random>

InstanceSet<CommonID> InstanceSystem::identities = InstanceSet<CommonID>();

template<>
uint16_t InstanceSet<uint16_t>::GetNew()
{
    uint16_t id = (uint16_t)rand();
    while (activeInstances.count(id))
    {
        id = (uint16_t)rand();
    }
    return id;
}

template<>
uint32_t InstanceSet<uint32_t>::GetNew()
{
    uint32_t id = (uint32_t)rand();
    while (activeInstances.count(id))
    {
        id = (uint32_t)rand();
    }
    return id;
}