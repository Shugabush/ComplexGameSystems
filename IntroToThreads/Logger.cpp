#include "Logger.h"

#include <iostream>
#include <fstream>
#include <mutex>

std::mutex queueLock;
bool shouldKill = false;

void WriteToFile(std::queue<std::string>* msgQueue, std::fstream* stream)
{
	while (!msgQueue->empty() || !shouldKill)
	{
		while (!msgQueue->empty())
		{
			queueLock.lock();

			*stream << msgQueue->front() << std::endl;
			msgQueue->pop();
			stream->flush();

			queueLock.unlock();
		}
	}

	stream->close();
}

Logger::Logger()
{
	Stream = nullptr;
}

Logger::~Logger()
{
	shouldKill = true;
	WriteThread.join();
	if (Stream != nullptr)
	{
		Stream->close();
	}
	delete Stream;
	Stream = nullptr;
}

void Logger::Init(const std::string& logFileName)
{
	Stream = new std::fstream(logFileName, std::ios::out);

	WriteThread = std::thread(WriteToFile, &Messages, Stream);
}

void Logger::Log(const std::string& logText)
{
	queueLock.lock();
	Messages.push(logText);
	queueLock.unlock();
}
