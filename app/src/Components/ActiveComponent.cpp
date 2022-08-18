#include "Components/Component.hpp"

ComponentRegister(ActiveComponent, Component)
bool ActiveComponent::IsActiveComponent()
{
    return true;
} 