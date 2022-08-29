# About
This is my crude attempt at my own engine written in entirely C++ using Dear ImGui, OpenGL, glm.

## Libraries
* Dear ImGui
* glm
* glfw
* glad

# Building
Building this requires little setup, I assume you know how to use cmake, it's just as simple as calling:

	cmake -B build -G "<generator>"

`<generator>` is an Build Tool Generator that you have installed.

## Windows
I personally use `MinGW Makefiles` and to set that up you'll have to download [msys2](https://www.msys2.org/), once installed run `MSYS MinGW` application and install the mingw64 package via:

	pacman -S mingw-w64-x86_64-gcc

I personally also use vscode to program, I have used visual studio community in the past it's great, but I am a masochist and I like compilation errors.

But in using vscode I have made a bunch of vscode tasks that can build this project in .vscode/tasks.json you can find the config that automatically runs cmake generate and cmake build called `"Cmake Generate"` and `"Cmake Build"` the first makes the build directory and the second compiles the code.  
Some older commits will require modification to this tasks.json to work, specifically around args, newer versions uses args array with objects with escaped quoting, see newer task.json for example.

# Systems
## Component System:

The component system is rudimentary and not a true ECS, it works by auto registering the class and variables to be displayed in the inspector have a special setup requirement, examples in [ComponentGenCpp.hpp](app/srcinc/Components/ComponentGenCpp.hpp)

## Entity System:
Entities can have components.  
Entities aren't required to have a transform.  
Entity class is a wrapper for the entity id's and it's scene. Using that information there are wrapper methods to call the scenes entity manipulation methods. ie Entities "SetName" method just "redirects" to the scenes "SetEntityName" passing in the entity id.

## Scene:
The scene stores all most everything, entities, their components, their heirarchial relation, the scene class has methods that manipulate this data.  
