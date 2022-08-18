#include "Input.hpp"
#include <iostream>
#include <GLFW/glfw3.h>

class GLFWwindow;

Input* Input::instance;
 
 
Input::Input()
{
    if(!instance)
        instance = this;

    keyBufferCurrent = keyBuffer1;
    keyBufferPrevious = keyBuffer2;
    keyBufferNext = keyBuffer3;
}

void Input::MouseIgnoreNextDelta()
{
    ignoreNextDelta = true;
}

void Input::OnMousePosChanged(GLFWwindow* window, double x, double y, getcursorposfun glfwGetCursorPos)
{
    if (firstTime)
    {
        glfwGetCursorPos(window, &prevMousePosX, &prevMousePosY);
        firstTime = false;
    }
    
    glfwGetCursorPos(window, &currentMousePosX, &currentMousePosY);


    mouseXDelta = currentMousePosX - prevMousePosX;
    mouseYDelta = prevMousePosY - currentMousePosY;

    if(ignoreNextDelta)
    {
        mouseXDelta = 0;
        mouseYDelta = 0;
        ignoreNextDelta = false;
    }

    prevMousePosX = currentMousePosX;
    prevMousePosY = currentMousePosY;

    for (auto &&cb : onMouseChangedArr)
    {
        cb(this);
    }
}

bool Input::isKeyDown(KeyCode key)
{
    return keyBufferPrevious[key] != DOWN && (keyBufferCurrent[key] == DOWN || keyBufferCurrent[key] == DECAY);
}

bool Input::isKeyUp(KeyCode key)
{
    return keyBufferCurrent[key] == UP || (keyBufferCurrent[key] == DOWN || keyBufferCurrent[key] == DECAY) && keyBufferCurrent[key] != DOWN;
}

bool Input::isKeyHeld(KeyCode key)
{
    return keyBufferPrevious[key] == DOWN && (keyBufferCurrent[key] == DOWN || keyBufferCurrent[key] == DECAY);
}

void Input::Refresh()
{
    RotateAndClearBuffers();
}

void Input::OnKeyboardCallback(KeyCode key, KeyState state)
{
    if (keyBufferNext[key] == KeyState::NONE)
    {
        keyBufferNext[key] = state;
    }
    
    if(keyBufferNext[key] == KeyState::DOWN && state == KeyState::UP)
    {
        keyBufferNext[key] = KeyState::DECAY;
    }
}

void Input::RotateAndClearBuffers()
{
    KeyState* ptemp = keyBufferPrevious;
    keyBufferPrevious = keyBufferCurrent;
    keyBufferCurrent = keyBufferNext;
    keyBufferNext = ptemp;

    for (int i = 0; i < INPUT_KEYCOUNT; i++) {
        if(keyBufferPrevious[i] == KeyState::DOWN && keyBufferCurrent[i] != KeyState::UP)
        {
            keyBufferCurrent[i] = KeyState::DOWN;
        }

        if(keyBufferPrevious[i] == KeyState::DECAY)
        {
            keyBufferPrevious[i] == KeyState::DOWN;
            keyBufferCurrent[i] == KeyState::UP;
        }

        keyBufferNext[i] = KeyState::NONE;
    }
}


void Input::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    if(!instance)
        return;

    if (key >= INPUT_KEYCOUNT || action == GLFW_REPEAT)
    {
        return;
    }

    instance->OnKeyboardCallback((KeyCode)key, action == GLFW_PRESS ? KeyState::DOWN : action == GLFW_RELEASE ? KeyState::UP : KeyState::NONE);
}