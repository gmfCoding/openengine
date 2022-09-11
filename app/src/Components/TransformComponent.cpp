#include "Components/Transform.hpp"
#include "Components/ComponentGenCpp.hpp"
#include "Core/Types.hpp"

#define mainType() TransformComponent
#define baseType() Component

// RegisterComponent(x(0),y(0),z(0))
CompID TransformComponent::CID;

namespace
{
    Component::Registrar<TransformComponent> registrar(STRINGIFY0(TransformComponent));
}

TransformComponent::TransformComponent() : x(0), y(0), z(0), Component(CID) { m_ComponentType = CID; }
TransformComponent::TransformComponent(CompID cid) : x(0), y(0), z(0), Component(cid) { m_ComponentType = cid; }
int TransformComponent::GetID() { return TransformComponent::CID; }
void TransformComponent::GetPropertiesLocal(std::vector<SObject *> &prop_list) { TransformComponent::GetProperties(prop_list); }
Component *TransformComponent::create() { return new TransformComponent(); }

BeginProperties(),
#define propType() float
    SProperty1(x),
    SProperty1(y),
    SProperty1(z),
#undef propType
#define propType() int
    SProperty1(a)
        EndProperties();

#include "CompGenClear.hpp"

// void TransformComponent::GetProperties(std::vector < SObject * > & prop_list) {
//   Component::GetProperties(prop_list);
//   static SObject props = {
//     {
//       "TransformComponent",
//       "Component",
//       0,
//       0
//     },
//     #define propType() float {
//       "x",
//       STRINGIFY0(float),
//       sizeof(float),
//       offsetOf( & TransformComponent::x)
//     },
//     {
//       "y",
//       STRINGIFY0(float),
//       sizeof(float),
//       offsetOf( & TransformComponent::y)
//     },
//     {
//       "z",
//       STRINGIFY0(float),
//       sizeof(float),
//       offsetOf( & TransformComponent::z)
//     },
//     {
//       "a",
//       STRINGIFY0(int),
//       sizeof(int),
//       offsetOf( & TransformComponent::a)
//     }
//   };
//   prop_list.push_back( & props);
// }
