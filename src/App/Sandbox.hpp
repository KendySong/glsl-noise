#pragma once
#include <map>
#include <vector>

#include "Timer.hpp"
#include "../Render/Shader.hpp"
#include "../Render/Rectangle.hpp"
#include "../Render/ShaderType.hpp"

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
	bool m_autoScroll;
	std::string m_gpu;
	
	//Framebuffer
	std::uint32_t m_fbo;
	std::uint32_t m_fbto;
	std::uint32_t m_rbo;
	gln::Rectangle m_planeShader;

	//Shaders
	bool m_pause;
	float m_elapsedTime;
	glm::vec2 m_resolution;
	std::map<std::string, Shader> m_shaders;

	//Noise settings
	ShaderType m_current;
	glm::vec2 m_pos;
	glm::vec2 m_size;
	std::int32_t m_octaves;
	float m_amplitude;
	float m_frequency;
	float m_persistence;
	float m_lacunarity;	
};