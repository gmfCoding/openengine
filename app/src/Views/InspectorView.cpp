#include "Views/InspectorView.hpp"
#include "Systems/Scenes.hpp"
#include "Editor.hpp"
#include "Components/Component.hpp"
#include "Components/TestComponent.hpp"
#include <string>

const ImVec2 size = ImVec2(300, 800);

void InspectorView::OnDrawGUI()
{
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    if (this->selected.Exists())
    {
        if(this->selected.GetName().length() == 0)
            return;

        ImGui::Text("Name:");
        ImGui::SameLine(); 
        if(ImGui::InputText("##Name:", this->selectedEntityName.data(), ImGuiInputTextFlags_EnterReturnsTrue ))
        {
            if(this->selectedEntityName[0] == '\0')
                this->selectedEntityName = "Entity";
            this->selected.SetName(this->selectedEntityName);
        }

        // std::vector<SObject*> properties;
        // for (auto e : this->selected->components)
        // {
        //     std::string s = std::string(ComponentSystem::Get()->GetName(e->m_ComponentType)) + "##" + std::to_string(e->m_instanceID);

        //     if (ImGui::CollapsingHeader(s.c_str(), ImGuiTreeNodeFlags_None))
        //     {
        //         // Our buttons are both drag sources and drag targets here!
        //         if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
        //         {
        //             // Set payload to carry the index of our item (could be anything)
        //             ImGui::SetDragDropPayload("DRAG_COMPONENT", &e, sizeof(Component*), ImGuiCond_Once);
        //             ImGui::EndDragDropSource();
        //         }

        //         e->GetPropertiesLocal(properties);

        //         for(auto p : properties)
        //         {
        //             for(auto p2 : p->properties)
        //             {
        //                 p2.second.ImGuiDraw(p2.first + "##" + s, e);

        //                 if (ComponentSystem::Get()->Exists(p2.second.type) && ImGui::BeginDragDropTarget())
        //                 {
        //                     std::cout << "Dropped Component::";
        //                     if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DRAG_COMPONENT"))
        //                     {
        //                         TestComponent* dropped = *(TestComponent**)payload->Data;

        //                         std::cout << dropped->m_instanceID << " of " << dropped->GET_COMPONENT_NAME() << std::endl;

        //                         if(dropped->GET_COMPONENT_NAME() == p2.second.type)
        //                         {
        //                             Component** dest = (Component**)p2.second.GetPtr((char*)e);
        //                             *dest = dropped;
        //                         }
        //                     }
        //                     ImGui::EndDragDropTarget();
        //                 }

                        
        //             }
        //         }

        //         properties.clear();
        //     }
        // }

        // if (ImGui::Button("Add Component"))
        //     ImGui::OpenPopup("my_component_popup");
        // if (ImGui::BeginPopup("my_component_popup", ImGuiWindowFlags_MenuBar))
        // {
        //     if(ImGui::ListBoxHeader("##AddComponents", size))
        //     {
        //         for (auto e : ComponentSystem::Get()->componentIdMap)
        //         {
                    
        //             if(e.second.compare(this->searchComponent) <= 0)
        //                 return;

        //             if(ImGui::Selectable(e.second.c_str(), false))
        //             {
        //                 this->selected.AddComponent();
        //             }
        //         }
        //         ImGui::ListBoxFooter();
        //     }

        //     ImGui::InputText("##ComponentSearch:", this->searchComponent.data(), 10);
        //     ImGui::EndPopup();
        // }
    }
}



void InspectorView::SelectEntity(Entity entity)
{
    Scene* scene = Scenes::Get(entity.scene);
    if(entity.GetName().length() == 0)
    {
        this->selectedEntityName = "Entity";
        entity.SetName(this->selectedEntityName);
    }
    this->selectedEntityName = std::string(entity.GetName());
    this->selected = entity;
}

