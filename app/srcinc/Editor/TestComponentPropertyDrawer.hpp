#include "Editor/PropertyField.hpp"
#include <string>

class TestComponentPropertyDrawer : public PropertyField
{
    public:
    TestComponentPropertyDrawer(const std::string& name);
    
    virtual void DrawField(void* data);
    static PropertyField* Generate();
};