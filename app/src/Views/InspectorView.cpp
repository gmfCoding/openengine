#include "Views/InspectorView.hpp"
#include "Systems/Scenes.hpp"
#include "Editor.hpp"
#include "Components/Component.hpp"
#include "Components/TestComponent.hpp"
#include <string>


#include "Core/ObjectReference.hpp" 

const ImVec2 size = ImVec2(300, 800);

void Draw(void* test)
{

}

void InspectorView::OnDrawGUI()
{
    auto a = &Draw;
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



        std::vector<SObject*> properties;
        for (auto comp : this->selected.GetAllComponents())
        {
            ObjectReference <Component> ref(comp);
            std::string s = std::string(ComponentSystem::Get()->GetName(ref->m_ComponentType)) + "##" + std::to_string(ref->m_instanceID);

            if (ImGui::CollapsingHeader(s.c_str(), ImGuiTreeNodeFlags_None))
            {
                // Our buttons are both drag sources and drag targets here!
                if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
                {
                    // Set payload to carry the index of our item (could be anything)
                    ImGui::SetDragDropPayload("DRAG_COMPONENT", &ref, sizeof(Component*), ImGuiCond_Once);
                    ImGui::EndDragDropSource();
                }

                ref->GetPropertiesLocal(properties);

            // For each properties list (each class has it's own, even base/super classes)
                for(auto p : properties)
                {
                    // For each properties in ^^each list
                    for(auto p2 : p->properties)
                    {


                        p2.second.ImGuiDraw(p2.first + "##" + s, ref.Get());
                        
                        if (p2.second.type.find("ObjectReference") != std::string::npos && ImGui::BeginDragDropTarget())
                        {
                            std::cout << "Dropped Component::";
                            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DRAG_COMPONENT"))
                            {
                                ObjectReference<Component> dropped = *(ObjectReference <Component>*)payload->Data;

                                std::cout << dropped->m_instanceID << " of " << dropped->GET_COMPONENT_NAME() << std::endl;
                                //TODO: instead check for dropped is assignable from p2's type

                                std::string cname = dropped->GET_COMPONENT_NAME();
                                if(cname == p2.second.GetGenericType())
                                {
                                    ObjectReference<Component>* dest = (ObjectReference<Component>*)p2.second.GetPtr((char*)ref.Get());
                                    *dest = dropped;
                                }
                            }
                            ImGui::EndDragDropTarget();
                        }

                        
                    }
                }

                properties.clear();
            }
        }

        if (ImGui::Button("Add Component"))
            ImGui::OpenPopup("my_component_popup");
        if (ImGui::BeginPopup("my_component_popup", ImGuiWindowFlags_MenuBar))
        {
            if(ImGui::ListBoxHeader("##AddComponents", size))
            {
                for (auto e : ComponentSystem::Get()->componentIdMap)
                {
                    if(e.second.compare(this->searchComponent) <= 0)
                        return;

                    if(ImGui::Selectable(e.second.c_str(), false))
                    {
                        this->selected.AddComponent(e.first);
                    }
                }
                ImGui::ListBoxFooter();
            }

            ImGui::InputText("##ComponentSearch:", this->searchComponent.data(), 10);
            ImGui::EndPopup();
        }
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

