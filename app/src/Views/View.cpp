#include <string>
#include "Views/ViewSystem.hpp"
#include "Views/View.hpp"

View::View(ViewSystem* pOwner, const std::string& name) : owner(pOwner), m_title(name)
{

}

void View::SetDirty(bool state)
{
    if(state)
        isDirty = true;
}

void View::AddToViewSystem()
{
    this->owner->AddView(this);
}

ImGuiWindowFlags View::GetFlags()
{
    return ImGuiWindowFlags_None;
}