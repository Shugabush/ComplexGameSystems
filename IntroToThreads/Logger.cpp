#include "Logger.h"

#include <mutex>
#include <fstream>

std::mutex queueLock;
bool shouldKill = false;

void WriteToFile(TCircularQueue<std::string>* msgQueue, std::fstream* stream)
{
	while (!msgQueue->Empty() || !shouldKill)
	{
		// before checking again, delay for a little bit
		std::this_thread::sleep_for(std::chrono::duration<float>(0.1f));

		while (!msgQueue->Empty())
		{
			queueLock.lock();

			*stream << msgQueue->Front() << std::endl;
			msgQueue->Pop();
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
	Term();
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
	Messages.Push(logText);
	queueLock.unlock();
}

void Logger::Term()
{
	shouldKill = true;
	if (WriteThread.joinable())
	{
		WriteThread.join();
	}
}
