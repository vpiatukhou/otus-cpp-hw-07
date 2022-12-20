#include "CommandProcessor.h"
#include <iostream>

using namespace Homework;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Please provide a block size." << std::endl;
        return -1;
    }

    try {
        CommandProcessor commandProcessor(std::atoi(argv[1]));
        
        std::string command;
        while (std::getline(std::cin, command)) {
            commandProcessor.process(command);
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}
