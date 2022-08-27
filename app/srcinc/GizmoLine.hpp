#ifndef GIZMO3D_H
#define GIZMO3D_H
#include "Object.hpp"
#include "LoadGlad.h"
#ifdef OE_SRC_USE_PCH
#include "pch/pch.hpp"
#else
#include <vector>
#endif
class ViewCamera;

class GizmoLine : public EngineObject {
    int shaderProgram;
    unsigned int VBO, VAO;
    std::vector<float> vertices;
    glm::vec3 startPoint;
    glm::vec3 endPoint;
    glm::mat4 MVP;
    glm::vec3 lineColor;
public:
    GizmoLine(glm::vec3 start, glm::vec3 end);

    int setMVP(glm::mat4 mvp);

    int setColor(glm::vec3 color);

    int draw(ViewCamera* camera);

    ~GizmoLine();
};


#endif