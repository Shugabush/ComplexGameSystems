#pragma once
#include <string>
#include <thread>

class Logger
{
public:
	Logger(std::string filenameToWriteTo);

	void Log(std::string text);

private:
	std::thread thread;
	std::string filename;
};