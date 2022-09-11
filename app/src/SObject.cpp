#include "SObject.hpp"
#include <iostream>
#include <string>
#include <sstream>

#include "imgui.h"
#include "imgui/imgui_internal.h"
#include "Components/TestComponent.hpp"
#include "Views/InspectorView.hpp"

SPropertyField::SPropertyField(int pSize, const std::string& pType, int pOffset) : size(pSize),type(pType), offset(pOffset) 
{

}

SObject::SObject(std::initializer_list<SPropertyConstructInfo> init)
{
    name = init.begin()->name;
    std::cout << "Created SObject for:" << name << std::endl;
    int i = 0;
    int sizeTotal = 0;
    for (auto n : init)
    {
        if(++i == 0)
            continue;
        properties.emplace(std::make_pair(n.name, SPropertyField(n.size, n.type, n.offset)));
    }
} 


void* SPropertyField::GetPtr(void* obj)
{
    return (void*)(((uint8_t*)obj) + this->offset);
}

/// @brief Draws an ImGui element specific to SPropertyField::type
/// @param name 
/// @param obj The parent object that contains the Property for this instance
void SPropertyField::ImGuiDraw(const std::string& name, void* obj, InspectorView* inspector)
{
    if(this->type == "int")
        ImGui::InputInt(name.c_str(), (int*)this->GetPtr(obj));
    else if(this->type == "float")
        ImGui::InputFloat(name.c_str(), (float*)(((char*)obj) + this->offset));
    else if(this->type == "std::string")
        ImGui::InputText(name.c_str(), ((std::string*)this->GetPtr(obj))->data(), 255);
    else if(this->type.find("ObjectReference") != std::string::npos)
    {
        ObjectReference<void> object = *(ObjectReference<void>*)GetPtr(obj);
        std::string buf = this->GetGenericType() + ":" + (object.IsValid() ? std::to_string(object.m_id) : "Empty") + "##" + name;

        ImGui::PushStyleColor(ImGuiCol_Border, (ImVec4)ImColor(204,204,204));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12);
        if(ImGui::ButtonEx(buf.c_str(), ImVec2(0,0), ImGuiButtonFlags_PressedOnDoubleClick | ImDrawFlags_RoundCornersAll))
        {
            inspector->OnObjectReferenceFind(object, buf);
        }
        ImGui::PopStyleVar(2);
        ImGui::PopStyleColor(1);
        ImGuiID firstID = ImGui::GetCurrentContext()->LastItemData.ID;
        auto firstRect = ImGui::GetCurrentContext()->LastItemData.Rect;
        ImGui::SameLine();
        ImGui::Text(name.substr(0, name.find("#")).c_str());
        auto second = ImGui::GetCurrentContext()->LastItemData.Rect;
        if(ImGui::BeginDragDropTargetCustom(ImRect(firstRect.Min, second.Max), firstID))
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DRAG_COMPONENT"))
            {
                std::cout << "Dropped Component::";
                ObjectReference<Component> dropped = *(ObjectReference <Component>*)payload->Data;
                std::cout << dropped->m_instanceID << " of " << dropped->GET_COMPONENT_NAME() << std::endl;
                //TODO: instead check for dropped is assignable from p2's type

                std::string cname = dropped->GET_COMPONENT_NAME();
                if(cname == GetGenericType())
                {
                    ObjectReference<Component>* dest = (ObjectReference<Component>*)GetPtr(obj);
                    *dest = dropped;
                }
            }

            ImGui::EndDragDropTarget();
        }
    }
    else
        ImGui::Text(name.c_str());
}

std::string SPropertyField::GetGenericType()
{
    size_t type_start = type.find('<') + 1;
    size_t type_end = type.find('>') - type_start;
    return type.substr(type_start, type_end);
}