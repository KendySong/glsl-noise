#include <iostream>
#include <glad/glad.h>

#include "Rectangle.hpp"


Rectangle::Rectangle(glm::vec3 position, glm::vec2 size) : position(position), size(size)
{
	glm::vec2 halfSize = size / 2.0f;
	Vertex vertices[] = {
		{  {halfSize.x,  halfSize.y, 0.0}, {}, {} },
		{  {halfSize.x, -halfSize.y, 0.0}, {}, {} },
		{ {-halfSize.x, -halfSize.y, 0.0}, {}, {} },
		{ {-halfSize.x,  halfSize.y, 0.0}, {}, {} }
	};

	std::uint32_t indices[] = {
		0, 1, 3, 
		1, 2, 3
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	Vertex::bind();
}

void Rectangle::draw()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}