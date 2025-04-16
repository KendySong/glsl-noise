#pragma once
#include <chrono>

class Timer
{
public :
	Timer();
	void start();
	void restart();	
	float getElapsedTime();
	float getDeltaTime();

private :
	std::chrono::system_clock::time_point m_start;
};