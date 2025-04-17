#pragma once
#include "Timer.hpp"
#include "../Render/Shader.hpp"
#include "../Render/Rectangle.hpp"

class Sandbox
{
public :
	Sandbox();
	void update();
	void handleGui();
	void draw();

private :
	void countFPS();

	int m_fps;
	int m_fpsCounter;
	Timer m_fpsChrono;

	Timer m_elapsed;
	Timer m_delta;

	//Framebuffer
	Shader m_main;
	std::uint32_t m_fbo;
	std::uint32_t m_fbto;
	std::uint32_t m_rbo;

	//Rectangle
	Rectangle m_planeShader;
};