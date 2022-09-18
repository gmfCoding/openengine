#include "Views/InspectorView.hpp"
#include "Systems/Scenes.hpp"

#include "Core/ObjectReference.hpp" 

#include "Components/Component.hpp"
#include "Components/TestComponent.hpp"

#include "Editor.hpp"
#include "Editor/PropertyField.hpp"

#include <string>
#include <unordered_set>

#include <imgui/imgui_internal.h>
#include <imgui_stdlib.hpp>


const ImGuiTableFlags table_flags =
        ImGuiTableFlags_BordersInnerV |
        // ImGuiTableFlags_BordersInnerH |
        ImGuiTableFlags_Resizable |
        ImGuiTableFlags_RowBg;

const ImVec2 size = ImVec2(300, 800);

std::vector<InspectorView*> InspectorView::inspectors;

std::unordered_map<EntityID, std::unordered_set<InspectorView*>> InspectorView::inspectorEntities;
std::unordered_map<EntityID, std::string>  InspectorView::selectedEntityNames;

std::vector<InspectorView*> InspectorView::GetInspectors(bool includeLocked)
{
    std::vector<InspectorView*> l_inspectors;
    for (auto i : inspectors)
    {
        if(i->locked == false || includeLocked)
            l_inspectors.push_back(i);
    }
    return l_inspectors;
}


void InspectorView::SetAllSelectedEntity(Entity entity)
{
    for (auto i : inspectors)
    {
        if(i->locked == false)
            i->SelectEntity(entity);
    }
}

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

        ImGui::EndMenuBar();
    }
    // ImGui::SameLine();


    // ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    if (this->selected.Exists())
    {
        if(this->selected.GetName().length() == 0)
            return;
            
        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted("Name");
        ImGui::SameLine();
        ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
        ImGui::SameLine();

        if(ImGui::InputText("##Name:", &this->selectedEntityNames[this->selected.id], ImGuiInputTextFlags_EnterReturnsTrue))
        {
            if(this->selectedEntityNames[this->selected.id][0] == '\0')
                this->selectedEntityNames[this->selected.id] = "Entity";
            this->selected.SetName(this->selectedEntityNames[this->selected.id]);
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

        ImGui::Separator();
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


void InspectorView::AddToViewSystem()
{
    View::AddToViewSystem();
    inspectors.push_back(this);
}

void InspectorView::SelectEntity(Entity entity)
{
    if(locked && selected.id != 0)
        return;


    Entity previous = this->selected;
    Scene* scene = Scenes::Get(entity.scene);
    if(entity.GetName().length() == 0)
    {
        this->selectedEntityNames[entity.id] = "Entity";
        entity.SetName(this->selectedEntityNames[entity.id]);
    }

    if(inspectorEntities.count(entity.id) == 0)
    {
        std::unordered_set<InspectorView*> inspectors;
        inspectorEntities.emplace(entity.id, inspectors);
    }

    if(previous.Exists())
        inspectorEntities[previous.id].erase(this);

    this->selectedEntityNames[entity.id] = std::string(entity.GetName());
    this->selected = entity;
    inspectorEntities[entity.id].emplace(this);
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