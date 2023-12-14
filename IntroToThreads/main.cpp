#include <thread>
#include <mutex>
#include <iostream>
#include <vector>

#include "Logger.h"

static std::mutex myMutex;

void Print()
{
	myMutex.lock();

	std::cout << "Hello Thread" << std::endl;
	
	myMutex.unlock();
}

int main()
{
	Logger logger;
	logger.Init("log.txt");

	logger.Log("Hello Log");
	logger.Log("Hello Log");
	logger.Log("Hello Log");
	logger.Log("Hello Log");
	logger.Log("Hello Log");

	return 0;
}