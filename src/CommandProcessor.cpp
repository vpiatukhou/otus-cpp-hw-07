#include "CommandProcessor.h"
#include "CommandWriter.h"
#include <stdexcept>

namespace Homework {

const std::string BEGIN_DYNAMIC_BLOCK_COMMAND = "{";
const std::string END_DYNAMIC_BLOCK_COMMAND = "}";

CommandProcessor::CommandProcessor(std::size_t blockSize_) : blockSize(blockSize_) {
    if (blockSize_ == 0) {
        throw std::invalid_argument("Block size must be greater than 0.");
    }
    commandBlock.reserve(blockSize_);
}

void CommandProcessor::process(const std::string& command) {
    if (command == BEGIN_DYNAMIC_BLOCK_COMMAND) {
        if (beginBlockCounter == 0) { //if not zero, it is a nested block => the command is ignored
            //begin a new dynamic block => write previous block
            writeCommands(commandBlock);
            commandBlock.clear();
        }
        ++beginBlockCounter;
    } else if (command == END_DYNAMIC_BLOCK_COMMAND) {
        --beginBlockCounter;
        if (beginBlockCounter == 0) {
            //end the dynamic block => write it
            writeCommands(commandBlock);
            commandBlock.clear();
        }
    } else {
        commandBlock.push_back(command);
        if (beginBlockCounter == 0 && commandBlock.size() == blockSize) {
            writeCommands(commandBlock);
            commandBlock.clear();
        }
    }
}

};