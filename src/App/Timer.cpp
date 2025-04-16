#include "Timer.hpp"

Timer::Timer()
{
	this->start();
}

void Timer::start()
{
	m_start = std::chrono::system_clock::now();
}

void Timer::restart()
{
	this->start();
}

float Timer::getElapsedTime()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(now - m_start).count() * 0.000001;
}

float Timer::getDeltaTime()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	float dt = std::chrono::duration_cast<std::chrono::microseconds>(now - m_start).count() * 0.000001;
	this->restart();
	return dt;
}