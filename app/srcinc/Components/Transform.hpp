#include <sstream>

#ifdef OE_SRC_USE_PCH
#include "pch/pch.hpp"
#else
#include <string>
#include <map>
#include <iostream>
#endif

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