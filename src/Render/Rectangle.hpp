#pragma once
#include <array>

#include "Vertex.hpp"

namespace gln {
    class Rectangle
    {
    public:
        Rectangle() = default;
        Rectangle(glm::vec3 position, glm::vec2 size);
        void draw();

        glm::vec3 position;
        glm::vec2 size;

        std::uint32_t vao;
        std::uint32_t vbo;
        std::uint32_t ebo;
    };
}
