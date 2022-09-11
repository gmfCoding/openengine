#include "Components/ComponentGenCpp.hpp"
#include "Components/TestComponent.hpp"

#define mainType() TestComponent
#define baseType() Component

RegisterComponent(dragMe(0), data("Hello, World!"))

BeginProperties(),
SProperty2(dragMe, ObjectReference<TestComponent>),
SProperty2(data, std::string)
EndProperties();

#include "CompGenClear.hpp"