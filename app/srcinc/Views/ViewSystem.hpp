#ifndef OE_VIEWS
#define OE_VIEWS
#include <vector>
#include <map>

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