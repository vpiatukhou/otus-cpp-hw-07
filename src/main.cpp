#include "CommandProcessor.h"
#include <iostream>

using namespace Homework;

const size_t NUMBER_OF_PARAMS_MIN = 2;
const size_t BLOCK_SIZE_PARAM_INDEX = 1;

int main(int argc, char** argv) {
    if (argc < NUMBER_OF_PARAMS_MIN) {
        std::cerr << "Please provide a block size." << std::endl;
        return -1;
    }

    try {
        std::size_t blockSize = std::stoi(argv[BLOCK_SIZE_PARAM_INDEX]);
        CommandProcessor commandProcessor(blockSize);
        
        std::string command;
        while (std::getline(std::cin, command)) {
            commandProcessor.process(command);
        }
    } catch (const std::logic_error& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}
