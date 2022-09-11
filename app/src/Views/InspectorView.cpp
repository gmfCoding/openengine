#include "Views/InspectorView.hpp"
#include "Systems/Scenes.hpp"
#include "Editor.hpp"
#include "Components/Component.hpp"
#include "Components/TestComponent.hpp"
#include <string>


#include "Core/ObjectReference.hpp" 
#include "Editor/PropertyField.hpp"
#include <imgui/imgui_internal.h>

const ImVec2 size = ImVec2(300, 800);



std::unordered_map<std::string, PropertyField*>& InspectorView::customPropertiesMap()
{
    static std::unordered_map<std::string, PropertyField*> customDrawers;
    return customDrawers;
}

void InspectorView::RegisterCustomPropertyDrawer(std::string type, PropertyField* propertyDrawer)
{
    std::cout << "Registered Custom Property Drawer:" << type << std::endl;
    customPropertiesMap().emplace(type, propertyDrawer);
}

void InspectorView::OnDrawGUI()
{
    if (ImGui::BeginMenuBar())
    {
        if(ImGui::Button(locked ? "LOCKED" : "UNLOCKED"))
        {
            std::cout << locked << std::endl;
            locked = !locked;
        }
            
        //ImGui::MenuItem(locked ? "LOCK" : "UNLOCK", NULL, &locked);
        ImGui::EndMenuBar();
    }
    // ImGui::SameLine();


    // ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

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

            if(navigate_to.find(s.c_str()) != std::string::npos)
                ImGui::SetNextItemOpen(true);

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
                    bool first = true;
                    // For each properties in ^^each list
                    for(auto p2 : p->properties)
                    {
                        // Skip the first because it is the component name
                        if (first)
                        { first = false; continue; }

                        if(customPropertiesMap().count(p2.second.type))
                        {
                            customPropertiesMap()[p2.second.type]->DrawField(p2.second.GetPtr(ref.Get()));
                        }
                        else
                        {
                            p2.second.ImGuiDraw(p2.first + "##" + s, ref.Get(), this);
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
    if(locked && selected.id != 0)
        return;

    Scene* scene = Scenes::Get(entity.scene);
    if(entity.GetName().length() == 0)
    {
        this->selectedEntityName = "Entity";
        entity.SetName(this->selectedEntityName);
    }
    this->selectedEntityName = std::string(entity.GetName());
    this->selected = entity;
}

void InspectorView::OnObjectReferenceFind(ObjectReference<void> object, const std::string& find)
{
    if(object.m_location == ObjectLocation::SCENE && object.IsValid())
    {
        Entity entity = Scenes::GetEntityFromComponentInstance(object.m_id);
        // GET THE ENTITY entity USING ObjectRerefence object's m_id
        // SET THE INSPECTORS SELECTED OBJECT TO ENTITY
        // SET THE INSPECTORS NAVIGATE_TO to the COMPONENT FIELD ON THAT ENTITY
        this->selected = entity;
        this->navigate_to = find;
    }
}

ImGuiWindowFlags InspectorView::GetFlags()
{
    return ImGuiWindowFlags_MenuBar;
}