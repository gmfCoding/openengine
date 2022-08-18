#include "Core/Object.hpp"
#include "Systems/InstanceSystem.hpp"

Object::Object() : instanceID(InstanceSystem::Get()->GetNew())
{

}