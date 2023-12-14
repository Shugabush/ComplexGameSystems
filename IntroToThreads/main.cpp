#include <thread>
#include <mutex>
#include <iostream>
#include <vector>

#include "Logger.h"
#include "TCircularQueue.h"

int main()
{
	/*Logger logger;
	logger.Init("log.txt");

	logger.Log("Hello Log 1");
	logger.Log("Hello Log 2");
	logger.Log("Hello Log 3");
	logger.Log("Hello Log 4");
	logger.Log("Hello Log 5");
	logger.Log("Hello Log 5");
	logger.Log("Hello Log 5");
	logger.Log("Hello Log 5");
	logger.Log("Hello Log 5");
	logger.Log("Hello Log 5");
	logger.Log("Hello Log 5");
	logger.Log("Hello Log 5");
	logger.Log("Hello Log 5");
	logger.Log("Hello Log 5");
	logger.Log("Hello Log 5");
	logger.Log("Hello Log 16");

	logger.Term();*/

	TCircularQueue<int> queue;
	queue.Push(0);
	queue.Push(5);
	queue.Push(7);
	queue.Push(8);
	queue.Push(15);
	queue.Push(25);
	queue.Push(1);
	queue.Push(2);
	queue.Push(12);
	queue.Push(3);
	queue.Push(2);
	queue.Push(4);
	queue.Push(41);
	queue.Push(14);
	queue.Push(37);
	queue.Push(35);

	queue.Reserve(20);

	queue.Push(35);
	queue.Push(37);
	queue.Push(32);

	while (!queue.Empty())
	{
		std::cout << queue.Front() << std::endl;
		queue.Pop();
	}

	return 0;
}