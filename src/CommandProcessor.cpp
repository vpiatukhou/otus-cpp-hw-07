#include "CommandProcessor.h"
#include "CommandWriter.h"

#include <stdexcept>

const std::string BEGIN_DYNAMIC_BLOCK_COMMAND = "{";
const std::string END_DYNAMIC_BLOCK_COMMAND = "}";

Homework::CommandProcessor::CommandProcessor(std::size_t blockSize_) : blockSize(blockSize_) {
    if (blockSize_ == 0) {
        throw std::invalid_argument("Block size must be greater than 0.");
    }
    commandBlock.reserve(blockSize_);
}

void Homework::CommandProcessor::process(const std::string& command) {
    if (command == BEGIN_DYNAMIC_BLOCK_COMMAND) {
        if (beginBlockCommandCounter == 0) { 
            //begin dynamic block => write previous block
            writeCommands(commandBlock);
            commandBlock.clear();
        }
        ++beginBlockCommandCounter;
    } else if (command == END_DYNAMIC_BLOCK_COMMAND) {
        --beginBlockCommandCounter;
        if (beginBlockCommandCounter == 0) {
            writeCommands(commandBlock);
            commandBlock.clear();
        }
    } else {
        commandBlock.push_back(command);
        if (beginBlockCommandCounter == 0 && commandBlock.size() == blockSize) {
            writeCommands(commandBlock);
            commandBlock.clear();
        }
    }
}
