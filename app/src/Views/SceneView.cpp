#include "Views/SceneView.hpp"
#include "Input.hpp"
#include "LoadGlad.h"

void SceneView::ControlScene()
{
    
#define KEYCONTROL(keyId, bvar) if(Input::instance->isKeyHeld(KeyCode::KEY_##keyId)) { bvar = true;} else{bvar = false;}
    KEYCONTROL(A,controls.Left)
    KEYCONTROL(S,controls.Backwards)
    KEYCONTROL(D,controls.Right)
    KEYCONTROL(W,controls.Forward)
    KEYCONTROL(Q,controls.Down)
    KEYCONTROL(E,controls.Up)
}