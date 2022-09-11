#include "Views/ViewSystem.hpp"
#include "hashing.hpp"

ViewSystem::ViewSystem(const Editor* pEditor) : editor(pEditor), views()
{

}

void ViewSystem::DrawAllViews()
{
    for (auto &&v : views)
    {
        ImGui::Begin(v.second->m_title.c_str(), nullptr, v.second->GetFlags());
        v.second->OnDrawGUI();
        ImGui::End();
    }
}

View* ViewSystem::GetView(const std::string& str)
{
    if(views.count(str))
        return views[str];
    return nullptr;
}

void ViewSystem::AddView(View* view)
{
    views.emplace(view->m_title, view);
}