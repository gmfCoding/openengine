#include "Components/ComponentSystem.hpp"
#include "hashing.hpp"
#include <vector>


ComponentSystem* ComponentSystem::instance;

CompID ComponentSystem::Register(const std::string& name, const std::string& parent)
{
    CompID id = Hashing::cid_const_hash(name.c_str());
    componentNameMap.emplace(name, id);
    componentIdMap.emplace(id, name);
    return id;
}

ComponentSystem* const ComponentSystem::Get()
{
    if(instance == nullptr)
        instance = new ComponentSystem();
    return instance;
} 

const std::string ComponentSystem::GetName(CompID id)
{
    if(componentIdMap.count(id))
        return componentIdMap[id];
    return "Unregistered Component";
}

bool ComponentSystem::Exists(std::string name)
{
    return componentNameMap.count(name) > 0;
}