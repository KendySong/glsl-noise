#pragma once
#include <fstream>
#include <windows.h>

#include "ConsoleColor.hpp"

class Log
{
public:
	static Log* instance() noexcept;
	void log(std::string log, int color = 15);
	std::string logs;
	int line;

private:
	Log();

	static Log* s_log;
	HANDLE m_hConsole;
	std::ofstream m_logStream;
};