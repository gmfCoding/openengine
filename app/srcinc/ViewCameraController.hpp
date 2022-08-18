#include "ViewCamera.hpp"
class ViewCamera;

class ViewCameraController {
    public:
    ViewCamera* camera;

    void Control(CameraControls move, float dt);
    void OnMouseInput(void* _input);
};
