#ifndef OE_VIEWS
#define OE_VIEWS


#ifdef OE_SRC_USE_PCH
#include "pch/pch.hpp"
#else
#include <vector>
#include <map>
#endif

#include "Views/View.hpp"

class Editor;


class ViewSystem
{
    std::map<std::string, View*> views = {};

public:
    const Editor* editor;

    ViewSystem(const Editor* pEditor);

    void DrawAllViews();
    View* GetView(const std::string& str);
    void AddView(View* view);
};
#endif