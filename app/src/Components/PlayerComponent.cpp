#include "Components/ComponentGenCpp.hpp"
#include "Components/PlayerComponent.hpp"

#define mainType() PlayerComponent
#define baseType() Component

RegisterComponent(name("Default_Player_Name"))

BeginProperties(),
SProperty2(name, std::string)
EndProperties();

#include "CompGenClear.hpp"