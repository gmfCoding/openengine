#include "Editor/PropertyField.hpp"
#include "Views/InspectorView.hpp"

PropertyField::PropertyField(const std::string& name) : type(name)
{

}

PropertyField* PropertyField::Generate()
{
    return nullptr;
}

void PropertyField::Register(PropertyField* property)
{
    InspectorView::RegisterCustomPropertyDrawer(property->type, property);
}