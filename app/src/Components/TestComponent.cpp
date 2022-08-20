#include "Components/ComponentGenCpp.hpp"
#include "Components/TestComponent.hpp"

#define mainType() TestComponent
#define baseType() Component

RegisterComponent(dragMe(nullptr), data("Hello, World!"))

BeginProperties(),
SProperty2(dragMe, TestComponent*),
SProperty2(data, std::string)
EndProperties();

#include "CompGenClear.hpp"