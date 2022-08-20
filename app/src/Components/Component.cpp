#include "Components/Component.hpp"
#include "Systems/InstanceSystem.hpp"
#include <unordered_map>

CompID Component::CID = ComponentSystem::Get()->Register("Component", "");
Component::Component(CompID comp_id)
{
    m_instanceID = InstanceSystem::identities.GetNew();
    m_ComponentType = comp_id;
    std::cout << "Made TransformComponent Instance:" << comp_id;
}

bool Component::IsActiveComponent()
{
    return false;
}

int Component::getExecutionOrder() {return 0;}


void Component::GetProperties(std::vector<SObject*>& prop_list)
{

}

void Component::registrate(std::string const & name, ComponentInfo * ci)
{
    ComponentSystem::Get()->Register(name, "");
    registry()[ci->hash] = ci;
}

Component* Component::instantiate(CompID cid)
{
    auto it = registry().find(cid);
    return it == registry().end() ? nullptr : (it->second)->creator();
}

std::unordered_map<CompID, ComponentInfo*> & Component::registry()
{
    static std::unordered_map<CompID, ComponentInfo*> impl;
    return impl;
}