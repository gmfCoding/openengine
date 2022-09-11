
#ifndef OE_TEST_COMPONENT
#define OE_TEST_COMPONENT
#include "Components/Component.hpp"
#include "Components/ComponentGenHpp.hpp"
#include <string>

class PlayerComponent;

ComponentDefinition(EnemyTurretAI, Component)

public:
    ObjectReference<PlayerComponent> target_to_shoot;
};

#endif