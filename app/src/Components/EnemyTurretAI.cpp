#include "Components/ComponentGenCpp.hpp"
#include "Components/EnemyTurretAI.hpp"
#include "Components/PlayerComponent.hpp"

#define mainType() EnemyTurretAI
#define baseType() Component

RegisterComponent(target_to_shoot(0))

BeginProperties(),
SProperty2(target_to_shoot, ObjectReference<PlayerComponent>),
EndProperties();

#include "CompGenClear.hpp"