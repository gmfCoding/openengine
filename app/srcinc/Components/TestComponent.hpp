
#ifndef OE_TEST_COMPONENT
#define OE_TEST_COMPONENT
#include "Components/Component.hpp"
#include "Components/ComponentGenHpp.hpp"
#include <string>

ComponentDefinition(TestComponent, Component)

public:
    TestComponent* dragMe;
    std::string data;
};

#endif