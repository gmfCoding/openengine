#include "SObject.hpp"
#include <iostream>
#include "imgui.h"
#include "Components/TestComponent.hpp"

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

void SPropertyField::ImGuiDraw(const std::string& name, void* obj)
{
    if(this->type == "int")
        ImGui::InputInt(name.c_str(), (int*)this->GetPtr(obj));
    else if(this->type == "float")
        ImGui::InputFloat(name.c_str(), (float*)(((char*)obj) + this->offset));
    else if(this->type == "std::string")
        ImGui::InputText(name.c_str(), ((std::string*)this->GetPtr(obj))->data(), 255);
    else if(this->type == "TestComponent")
    {
        TestComponent* c = (*(TestComponent**)this->GetPtr(obj));
        if(c != nullptr)
            ImGui::Text(c->data.c_str());
        else
            ImGui::Text("TestComponent_Unset");
    }
    else
        ImGui::Text(name.c_str());
}