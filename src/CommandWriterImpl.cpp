#include "CommandWriterImpl.h"

#include <chrono>
#include <iostream>
#include <fstream>

namespace Homework {

const std::string BLOCK_PREFIX = "bulk: ";
const std::string COMMAND_DELIMITER = ", ";
const std::string FILENAME_PREFIX = "bulk";
const std::string FILE_EXTENSION = ".log";

void CommandWriterImpl::writeToStream(std::ostream& ostream, const std::vector<std::string>& commands) const {
    ostream << BLOCK_PREFIX << commands[0];
    for (std::size_t i = 1; i < commands.size(); ++i) {
        ostream << COMMAND_DELIMITER << commands[i];
    }
}

void CommandWriterImpl::writeToFile(const std::vector<std::string>& commands) const {
    auto timeSinceEpoch = std::chrono::system_clock::now().time_since_epoch();
    auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(timeSinceEpoch).count();

    std::string filename = FILENAME_PREFIX;
    filename += std::to_string(timestamp);
    filename += FILE_EXTENSION;

    std::ofstream file(filename);
    writeToStream(file, commands);
    file.flush();
    file.close();
}

void CommandWriterImpl::write(const std::vector<std::string>& commands) const {
    writeToStream(std::cout, commands);
    std::cout << std::endl;

    writeToFile(commands);
}

};
