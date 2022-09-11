
#ifndef OE_PLAYER_COMPONENT
#define OE_PLAYER_COMPONENT
#include "Components/Component.hpp"
#include "Components/ComponentGenHpp.hpp"
#include <string>

ComponentDefinition(PlayerComponent, Component)

public:
    std::string name;
};
#endif