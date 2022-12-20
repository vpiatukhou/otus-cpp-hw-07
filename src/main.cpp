#include "CommandProcessor.h"
#include <iostream>

using namespace Homework;

int main(int argc, char** argv)
{
	if (argc < 2) {
		std::cout << "Please provide a block size." << std::endl;
		return 0;
	}

	CommandProcessor commandProcessor(std::atoi(argv[0]));
	
	std::string command;
	while (std::getline(std::cin, command)) {
		commandProcessor.process(command);
	}
	return 0;
}
