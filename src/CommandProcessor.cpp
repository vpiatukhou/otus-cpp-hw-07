#include "CommandProcessor.h"
#include "CommandWriter.h"

const std::string BEGIN_DYNAMIC_BLOCK_CMD = "{";
const std::string END_DYNAMIC_BLOCK_CMD = "}";

void Homework::CommandProcessor::process(const std::string& command) {
	size_t bracesCounter = 0;

	if (command == BEGIN_DYNAMIC_BLOCK_CMD) {
		if (bracesCounter == 0) {
			writeCommands(commandBlock);
			commandBlock.clear();
		}
		++bracesCounter;
	} else if (command == END_DYNAMIC_BLOCK_CMD) {
		--bracesCounter;
		if (bracesCounter == 0) {
			writeCommands(commandBlock);
			commandBlock.clear();
		}
	} else {
		commandBlock.push_back(command);
		if (bracesCounter == 0 && commandBlock.size() == blockSize) {
			writeCommands(commandBlock);
			commandBlock.clear();
		}
	}
}
