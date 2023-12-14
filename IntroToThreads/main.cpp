#include <thread>
#include <mutex>
#include <iostream>
#include <vector>

#include "Logger.h"

int main()
{
	Logger logger;
	logger.Init("log.txt");

	logger.Log("Hello Log");
	logger.Log("Hello Log");
	logger.Log("Hello Log");
	logger.Log("Hello Log");
	logger.Log("Hello Log");

	logger.Term();

	return 0;
}