#pragma once

#include <thread>
#include <string>
#include <queue>
#include <fstream>

class Logger
{
	std::fstream* Stream;

	std::thread WriteThread;

	std::queue<std::string> Messages;

public:
	Logger();
	~Logger();

	void Init(const std::string& logFileName);
	void Log(const std::string& logText);

private:
};