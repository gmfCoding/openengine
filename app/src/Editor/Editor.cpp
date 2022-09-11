#include <iostream>
#include "Editor.hpp"
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Systems/InstanceSystem.hpp"
#include "Components/ComponentSystem.hpp"
#include "Components/Transform.hpp"

#include "Core/Scene.hpp"
#include "Systems/Scenes.hpp"

#include <glm/glm.hpp>
#include "gmfc_image.hpp"

#include "Editor/PropertyField.hpp"
class TestComponentPropertyDrawer : public PropertyField
{
    public:
    TestComponentPropertyDrawer(const std::string& name);
    virtual void DrawField(void* data);
    static PropertyField* Generate();
};

Editor* Editor::instance;

void cursorpos_callback(GLFWwindow* window, double x, double y)
{
    Editor::Get()->input->OnMousePosChanged(window, x, y, glfwGetCursorPos);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


template<typename T, typename U> constexpr size_t offsetOf2(U T::*member)
{
    return (char*)&((T*)nullptr->*member) - (char*)nullptr;
}
// Create a OpenGL texture identifier
GLuint image_texture;

int Editor::OnInitialise()
{
    this->width = 1280;
    this->height = 720;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    window = glfwCreateWindow(width, height, "OpenEngine", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, Input::glfw_key_callback);
    glfwSetCursorPosCallback(window, cursorpos_callback);  
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui_ImplGlfw_InitForOpenGL(window, true);




    Input::instance = new Input();
    this->input = Input::instance;
    this->viewSystem = new ViewSystem(this);
    
    Scenes::LoadScene(Scenes::CreateScene());
    this->defaultScene = Scenes::current;


    auto one = this->defaultScene->CreateEntity();
    auto two = this->defaultScene->CreateEntity(one);
    auto three = this->defaultScene->CreateEntity(two);
    auto four = this->defaultScene->CreateEntity(one);
    auto five = this->defaultScene->CreateEntity();
    auto six = this->defaultScene->CreateEntity(five);

    std::vector<Entity> ents = {one, two, three, four, five, six};
    for (size_t i = 0; i < ents.size(); i++)
    {
        ents[i].SetName("Entity" + std::to_string(i));
    }
    
    targetFPS = 144;

    SetupDefaultViews();

    return 0;
}

void Editor::EscapeControl()
{
    if(input->isKeyDown(KeyCode::KEY_ESCAPE))
    {
        hideMouse = !hideMouse;

        glfwSetInputMode(window, GLFW_CURSOR, hideMouse ? GLFW_CURSOR_DISABLED: GLFW_CURSOR_NORMAL); 
        Input::instance->MouseIgnoreNextDelta();
    }
}
bool test = true;
void Editor::EditorUpdate()
{
    glClearColor(.7,.7,.7,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    EscapeControl();
    
    ImGui::ShowDemoWindow(&test);
    
    this->viewSystem->DrawAllViews();

    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);  
}


int Editor::Run()
{
    InstanceSystem* system = new InstanceSystem();
    this->OnInitialise();
    if(!instance)
        Editor::instance = this;

    glEnable(GL_DEPTH_TEST);  
    glEnable(GL_CULL_FACE); 
    glViewport(0, 0, this->width, this->width);

    glEnable(GL_DEBUG_OUTPUT);

    double lasttime = glfwGetTime();
    float deltaTime = 0.0f;
    float timeLastFrame = 0.0f;

    while(!glfwWindowShouldClose(window) && !quit) {
        input->Refresh();
        deltaTime =  glfwGetTime() - timeLastFrame;
        timeLastFrame = glfwGetTime();
        EditorUpdate();

        while (limitFPS && glfwGetTime() < lasttime + 1.0/targetFPS) {
            // TODO: Put the thread to sleep, yield, or simply do nothing
        }
        
        lasttime += 1.0/targetFPS;

        glfwPollEvents();  
    }
    glfwTerminate();
    return 0;
}



Editor* Editor::Get()
{
    return Editor::instance;
}