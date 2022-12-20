#include "CommandWriter.h"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <fstream>

const char NEWLINE = '\n';
const std::string FILENAME_PREFIX = "bulk";
const std::string FILE_EXTENSION = ".log";

void writeToConsole(const std::vector<std::string>& commands) {
	for (const std::string& command : commands) {
		std::cout << command << std::endl;
	}
}

void writeToFile(const std::vector<std::string>& commands) {
	auto timeSinceEpoch = std::chrono::system_clock::now().time_since_epoch();
	auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(timeSinceEpoch).count();
	
	std::string filename = FILENAME_PREFIX;
	filename += std::to_string(timestamp);
	filename += FILE_EXTENSION;

	std::ofstream file(filename);
	for (const std::string& command : commands) {
		file << command << NEWLINE;
	}
}

void Homework::writeCommands(const std::vector<std::string>& commands) {
	writeToConsole(commands);
	writeToFile(commands);
}
