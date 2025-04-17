#pragma once
#include <glm/glm.hpp>

class Vertex
{
public :
    Vertex() = default;
    Vertex(glm::vec3 pos, glm::vec2 uv, glm::vec3 color);
    static void bind();

    glm::vec3 pos;
    glm::vec2 uv;
    glm::vec3 color;

private :
};