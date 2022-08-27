#pragma once


#ifdef OE_SRC_USE_PCH
#include "pch/pch.hpp"
#else
#include <map>
#include <string>
#endif

#include "LoadGlad.h"
#include "fileio.hpp"

#include "Mesh.hpp"
#include "ViewCamera.hpp"

class EngineObject;

class Shader {
    public:
    GLuint shaderProgram;
};

struct MeshRenderer
{
    GLuint m_vao, m_vbo, m_ibo;
    bool vao_gen, vbo_gen, ibo_gen;

    GLuint texture;
    Mesh* m_mesh;
    GLsizei m_size;
    const std::string& materialName;
    Shader* shader;

    MeshRenderer(const std::string& material) : materialName(material), m_size(0), texture(0), vao_gen(false), vbo_gen(false), ibo_gen(false)
    {

    }

    void Render();
    void SetVertices(Mesh* mesh, int vao, int vbo);
    void SetIndices(Mesh* mesh, int vao, int ibo, int* size);

    
    void Bind(Mesh* mesh);
};

enum ShaderType {FRAGMENT = GL_FRAGMENT_SHADER, VERTEX = GL_VERTEX_SHADER};

struct CreateProgramArgument {
    std::string& path;
    ShaderType type;
};



class Renderer {
    public:
    static ViewCamera* camera;
    
};

using Index = unsigned int;

struct Vertex {
    glm::vec3  position;
    glm::vec2  texcoord;
};