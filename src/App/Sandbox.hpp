#pragma once
#include "Timer.hpp"

class Sandbox
{
public :
	Sandbox();
	void update();
	void handleGui();
	void render();

private :
	void countFPS();

	int m_fps;
	int m_fpsCounter;
	Timer m_fpsChrono;

	Timer m_elapsed;
	Timer m_delta;
};