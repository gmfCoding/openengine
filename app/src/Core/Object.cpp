#include "Core/Object.hpp"
#include "Systems/InstanceSystem.hpp"

Object::Object() : instanceID(InstanceSystem::identities.GetNew())
{

}