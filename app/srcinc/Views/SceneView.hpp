#ifndef OE_SCENE_VIEW
#define OE_SCENE_VIEW
#include "View.hpp"
#include "ViewCamera.hpp"

class SceneView : public View
{
    ViewCamera camera;
    CameraControls controls;

    public:
    void OnDrawGUI();
    void Render3DScene();
    void ControlScene();
};

#endif