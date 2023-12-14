#include "Logger.h"

#include <iostream>
#include <fstream>

void Print(std::string text, std::string filenameToWriteTo);

Logger::Logger(std::string filenameToWriteTo)
{
	filename = filenameToWriteTo;
}

void Logger::Log(std::string text)
{
	thread = std::thread(Print, text, filename);
	thread.join();
}

void Print(std::string text, std::string filenameToWriteTo)
{
	std::string existingText;

	// Read text from the file if it exists,
	// and add that 
	std::ifstream readFile(filenameToWriteTo);
	if (readFile.is_open())
	{
		std::string line;
		while (std::getline(readFile, line))
		{
			existingText += line + "\n";
		}
	}

	std::ofstream myFile;
	myFile.open(filenameToWriteTo);
	myFile << existingText + text + "\n";
	myFile.close();
}
