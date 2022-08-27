

#ifdef OE_SRC_USE_PCH
#include "pch/pch.hpp"
#else
#include <vector>
#endif

#include <functional>

#include "KeyCodes.h"
#ifndef OE_INPUT
#define OE_INPUT
struct GLFWwindow;

#ifndef def_getcursorposfun
typedef void (* getcursorposfun)(GLFWwindow*, double*,double*);
#endif

#define INPUT_KEYCOUNT 348



class Input {
    double prevMousePosX = 400;
    double prevMousePosY = 300;
public:

    double currentMousePosX;
    double currentMousePosY;

    double mouseXDelta = 0;
    double mouseYDelta = 0;
    bool ignoreNextDelta = false;

    bool firstTime = true;

    KeyState keyBuffer1[INPUT_KEYCOUNT];
    KeyState keyBuffer2[INPUT_KEYCOUNT];
    KeyState keyBuffer3[INPUT_KEYCOUNT];

    KeyState* keyBufferCurrent;
    KeyState* keyBufferPrevious;
    KeyState* keyBufferNext;

    static Input* instance;

    void OnMousePosChanged(GLFWwindow* window, double x, double y, getcursorposfun getcursor);
    std::vector<std::function<void(void*)>> onMouseChangedArr;

    Input();

    bool isKeyDown(KeyCode key);

    bool isKeyUp(KeyCode key);

    bool isKeyHeld(KeyCode key);

    void Refresh();

    void OnKeyboardCallback(KeyCode key, KeyState state);
    static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


    void RotateAndClearBuffers();

    void MouseIgnoreNextDelta();
};

#endif
// enum KeyMode{
//     None,
//     Press,
//     Hold,
//     Release
// };