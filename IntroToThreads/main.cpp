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
	Logger logger("log.txt");

	logger.Log("100");

	return 0;
}