#pragma once
#include <string>
#include <glad/glad.h>

class Shader
{
public :
	Shader(std::string vertex, std::string fragment);
	void bind();
	int id;
private :

};