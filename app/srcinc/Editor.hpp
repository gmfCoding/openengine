#ifndef OE_EDITOR
#define OE_EDITOR
#include "LoadGlad.h"
#include "Views/ViewSystem.hpp"
#include "Input.hpp"


class Scene;

class Editor
{
    ViewSystem* viewSystem;
    static Editor* instance;

    int width;
    int height;
    int targetFPS = 144;
    bool limitFPS = true;

    public:
    GLFWwindow* window;
    Input* input;
    bool quit;
    bool hideMouse;
    Scene* defaultScene;

    int OnInitialise();
    int Run();
    static Editor* Get();
    ViewSystem* GetViewSystem();

    void SetupDefaultViews();

    void EscapeControl();
    void EditorUpdate();

    void* ImGuiFromString(const std::string& type, void* data);
};

#endif