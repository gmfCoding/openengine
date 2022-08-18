#include "Views/HierarchyView.hpp"
#include "Views/InspectorView.hpp"
#include "Editor.hpp"

class ViewSystem;

void Editor::SetupDefaultViews()
{
    (new HierarchyView(this->viewSystem, "Hierarchy"))->AddToViewSystem();
    (new InspectorView(this->viewSystem, "Inspector"))->AddToViewSystem();
}