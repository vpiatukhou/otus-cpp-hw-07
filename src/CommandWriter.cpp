#include "CommandWriter.h"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <fstream>

const char NEWLINE = '\n';
const std::string BLOCK_PREFIX = "bulk";
const std::string FILENAME_PREFIX = "bulk";
const std::string FILE_EXTENSION = ".log";

namespace Homework {

void writeCommandsToStream(std::ostream& ostream, const std::vector<std::string>& commands) {
    if (commands.empty()) {
        return;
    }
    ostream << BLOCK_PREFIX << ": " << commands[0];
    for (std::size_t i = 1; i < commands.size(); ++i) {
        ostream << ", " << commands[i];
    }
    ostream << std::endl;
}

void writeCommandsToFile(const std::vector<std::string>& commands) {
    auto timeSinceEpoch = std::chrono::system_clock::now().time_since_epoch();
    auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(timeSinceEpoch).count();
    
    std::string filename = FILENAME_PREFIX;
    filename += std::to_string(timestamp);
    filename += FILE_EXTENSION;

    std::ofstream file(filename);
    writeCommandsToStream(file, commands);
}

void writeCommands(const std::vector<std::string>& commands) {
    writeCommandsToStream(std::cout, commands);
    writeCommandsToFile(commands);
}

};
