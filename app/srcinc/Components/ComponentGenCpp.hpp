#include "macros.hpp"

#define BeginProperties() BeginProperties2(mainType(), baseType())
#define BeginProperties2(type, baseType) void type::GetProperties(std::vector<SObject*>& prop_list) { baseType::GetProperties(prop_list); \
    static SObject props =\
    {\
        {STRINGIFY0(type),"Component", 0, 0}

#define EndProperties() }; prop_list.push_back(&props); }

#define SProperty1(name) SProperty2(name, propType())
#define SProperty2(name, type) SProperty3(name, type, propOwner())
#define SProperty3(name, type, owner) {#name,STRINGIFY0(type),sizeof(type), offsetOf(&owner::name)}


#define RegisterComponent(...) RegisterComponent2(mainType(), baseType(), __VA_ARGS__)
#define RegisterComponent2(type, base, ...) CompID type::CID;\
namespace\
{\
    Component::Registrar<type> registrar(STRINGIFY0(type), &type::CID);\
}\
type::type() : __VA_ARGS__ , base(CID) {\
    m_ComponentType = CID;\
}\
type::type(CompID cid) : __VA_ARGS__ , base(cid) {\
    m_ComponentType = cid;\
}\
int type::GetID() {\
    return type::CID;\
}\
void type::GetPropertiesLocal(std::vector<SObject*> & prop_list) {\
    type::GetProperties(prop_list);\
}\
Component * type::create() {\
    return new type();\
}

#define propOwner() mainType()