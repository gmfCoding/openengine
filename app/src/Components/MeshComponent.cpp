#include "Components/ComponentGenCpp.hpp"
#include "Components/MeshComponent.hpp"

#include "Mesh.hpp"
#define mainType() MeshComponent
#define baseType() Component

RegisterComponent(m_mesh(nullptr))

BeginProperties()
EndProperties();

#include "CompGenClear.hpp"