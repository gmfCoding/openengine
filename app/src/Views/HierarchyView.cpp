#include <iostream>
#include "Views/HierarchyView.hpp"
#include "Views/InspectorView.hpp"

#include "Core/Scene.hpp"
#include "Editor.hpp"

#include "imgui/imgui_internal.h"

const ImVec2 size = ImVec2(300, 800);

ImRect hierarchyTreeRect;

void HierarchyView::OnDrawGUI()
{
    if (ImGui::Button("Add Object"))
    {
        Entity e = Editor::Get()->defaultScene->CreateEntity();
        InspectorView::SetAllSelectedEntity(e);
    }

    if (ImGui::ListBoxHeader("Entities:", size))
    {
        hierarchyTreeRect = ImGui::GetCurrentContext()->LastItemData.Rect;

        ImGui_RecurseStartDrawHeirarchy(Editor::Get()->defaultScene);
    }
}
bool dirty = false;
void HierarchyView::ImGui_RecurseStartDrawHeirarchy(Scene *scene)
{
    for (auto e : scene->root)
    {
        ImGui_RecurseDrawHeirarchy(e, scene);
    }
    ImGui::ListBoxFooter();

    dirty = false;
}
struct ImGuiContext;



void HierarchyView::ImGui_RecurseDrawHeirarchy(EntityHierarchyNode *node, Scene *scene)
{
    if(dirty)
        return;

    Entity e = Entity{node->m_id, scene->GetSceneID()};
    ImGuiTreeNodeFlags flags = (this->selected.id == node->m_id ? ImGuiTreeNodeFlags_Selected : 0) | (node->m_nodes.size() > 0 ? ImGuiTreeNodeFlags_OpenOnArrow : ImGuiTreeNodeFlags_Leaf);


    if(this->selected.id == node->m_id && ImGui::IsKeyPressed(ImGuiKey_Delete))
    {
        scene->DeleteEntity(Entity {node->m_id, scene->GetSceneID()});
    }

    //ImGui::Text("%s_above", e.id);
    bool open = ImGui::TreeNodeEx(std::to_string(node->m_id).c_str(), flags, e.GetName().c_str());
    // char b[50];
    // sprintf(b, "**_%i_below", e.id);

    //ImGui::Separator();

    // Our buttons are both drag sources and drag targets here!
    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_AcceptNoDrawDefaultRect))
    {
        // Set payload to carry the index of our item (could be anything)
        ImGui::SetDragDropPayload("DRAG_ENTITY", &e, sizeof(Entity), ImGuiCond_Once);
        ImGui::EndDragDropSource();
    }
    
    if (ImGui::BeginDragDropTarget())
    {
        ImGuiContext* c = ImGui::GetCurrentContext();
        auto rect = c->LastItemData.Rect;
        auto mp = ImGui::GetIO().MousePos;

        auto upper = mp.y < (rect.GetCenter().y - rect.GetHeight()/6);
        auto lower =  mp.y > (rect.GetCenter().y + rect.GetHeight()/6);
        
        float size = hierarchyTreeRect.GetWidth();
        const int width = 2;
        const int offset = 1;

        
        if(upper)
        {
            ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(rect.Min.x, rect.Min.y - offset), ImVec2(rect.Min.x + size, rect.Min.y - (width + offset)), ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, 0.4f, 1.0f, 1.0f)));
        }
        else if (lower)
        {
            ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(rect.Min.x, rect.Max.y + offset), ImVec2(rect.Min.x + size, rect.Max.y + (width + offset)), ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, 0.4f, 1.0f, 1.0f)));
        }
        
        if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("DRAG_ENTITY"))
        {
            dirty = true;
            Entity first = *(Entity *)payload->Data;


            auto pn = scene->root;
            if(node->m_parent)
                pn = node->m_parent->m_nodes;

            int selfIndex = std::distance(pn.begin(), std::find(pn.begin(), pn.end(), node));

            if(upper)
            {
                first.SetParent(Entity { node->m_parent->m_id, scene->GetSceneID()}, selfIndex - 1);
            }
            else if (lower)
            {
                first.SetParent(Entity { node->m_parent->m_id, scene->GetSceneID()}, selfIndex + 1);
            } 
            else 
            {
                first.SetParent(Entity { node->m_id, scene->GetSceneID()});
            }

            std::cout << "Dropped" << first.GetName() << " on " << e.GetName();
        }
    }

    if (ImGui::IsItemClicked())
    {
        std::cout << "Selected:" << e.GetName() << std::endl;

        InspectorView::SetAllSelectedEntity(e);
        this->selected = e;
    }

    if (!open)
        return;

    for (auto e : node->m_nodes)
    {
        ImGui_RecurseDrawHeirarchy(e, scene);
    }

    ImGui::TreePop();
}