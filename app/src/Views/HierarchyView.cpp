#include <iostream>
#include "Views/HierarchyView.hpp"
#include "Views/InspectorView.hpp"

#include "Core/Scene.hpp"
#include "Editor.hpp"

const ImVec2 size = ImVec2(300, 800);
InspectorView* iv;

void HierarchyView::OnDrawGUI()
{
    iv = (InspectorView*)this->owner->GetView("Inspector");
    if(ImGui::Button("Add Object"))
    {
        Entity e = Editor::Get()->defaultScene->CreateEntity();
        iv->SelectEntity(e);
    }

    if(ImGui::ListBoxHeader("Entities:", size))
    {
        ImGui_RecurseStartDrawHeirarchy(Editor::Get()->defaultScene);
    }
}

void HierarchyView::ImGui_RecurseStartDrawHeirarchy(Scene* scene)
{
    for (auto e : scene->root)
    {
        ImGui_RecurseDrawHeirarchy(e, scene);
    }
    ImGui::ListBoxFooter();
}

void HierarchyView::ImGui_RecurseDrawHeirarchy(EntityHierarchyNode* node, Scene* scene)
{
    Entity e = Entity {node->m_id, scene->GetSceneID()};
    ImGuiTreeNodeFlags flags = ( this->selected.id == node->m_id ? ImGuiTreeNodeFlags_Selected  : 0) | (node->m_nodes.size() > 0 ? ImGuiTreeNodeFlags_OpenOnArrow : ImGuiTreeNodeFlags_Leaf);

    bool open = ImGui::TreeNodeEx(std::to_string(node->m_id).c_str(), flags, e.GetName().c_str());

    if(ImGui::IsItemClicked())
    {
        std::cout << "Selected:" << e.GetName() << std::endl;
        iv->SelectEntity(e);
        this->selected = e;
    }

    if(!open)
        return;

    for (auto e : node->m_nodes)
    {
        ImGui_RecurseDrawHeirarchy(e, scene);
        
    }

    ImGui::TreePop();
}