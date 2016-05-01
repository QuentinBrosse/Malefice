#pragma once
#include "easylogging++.h"

class Logger
{
public:
	Logger()	= delete;
	~Logger()	= delete;

	static void	setup(int argc, char* argv[], const std::string& filepath);
};
