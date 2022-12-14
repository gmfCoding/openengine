#include "Core/Types.hpp"

#define COMPONENT_REGISTER(type, base) public:\
static SObject properties;\
type(CompID comp_id);\
type();\
void GetPropertiesLocal(std::vector < SObject * > & prop_list) override;\
int GetID() override;\
static void GetProperties(std::vector<SObject*>& prop_list);\
static Component * create();\
COMPONENT_BASE_REGISTER(type)\
private:

#define COMPONENT_BASE_REGISTER(type) public:const std::string GET_COMPONENT_NAME() {return #type;} static CompID CID;

#define ComponentRegister(self,base) CompID self::CID = ComponentSystem::Get()->Register(#self, #base);
#define ComponentDefinition(self,base) class self : public base { COMPONENT_REGISTER(self, base)