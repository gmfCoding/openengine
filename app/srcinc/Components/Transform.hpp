#include <sstream>
#include <string>
#include <map>
#include <iostream>

#include "Components/ComponentGenHpp.hpp"
#include "Components/Component.hpp"

#include "Core/Types.hpp"

ComponentDefinition(TransformComponent, Component)
    public:

    TransformComponent* parent;
    public:
    float x, y, z;
    int a;
};