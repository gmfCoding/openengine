#pragma once

#include "pch/pch.hpp"
#include <glm/glm.hpp>

class Mesh {
    public:
    std::vector<glm::vec3> vertices;
    std::vector<unsigned short> indices;
    std::vector<glm::vec2> uvs;
};