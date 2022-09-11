#include "Views/InspectorView.hpp"
#include "Editor/PropertyField.hpp"
#include "Components/TestComponent.hpp"

#include "Editor/TestComponentPropertyDrawer.hpp"



// namespace
// {
//    PropertyFieldRegistrar<TestComponentPropertyDrawer> registrar("");
// }

TestComponentPropertyDrawer::TestComponentPropertyDrawer(const std::string& name) : PropertyField(name)
{

}

void TestComponentPropertyDrawer::DrawField(void* data)
{
    ObjectReference<TestComponent> dest = *(ObjectReference<TestComponent>*)data;
    if(dest.IsValid())
        ImGui::Text(dest->data.c_str());
    else
        ImGui::Text("TestComponent_Unset");
}

PropertyField* TestComponentPropertyDrawer::Generate()
{
    return new TestComponentPropertyDrawer("ObjectReference<TestComponent>");
}