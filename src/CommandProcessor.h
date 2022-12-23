#pragma once

#include "CommandWriter.h"
#include <cstddef>
#include <string>
#include <vector>

namespace Homework {

class CommandProcessor {

public:
    CommandProcessor(CommandWriter& commandWriter_, std::size_t blockSize_);

    void process(const std::string& command);
    void flush();

private:
    std::size_t blockSize;
    std::vector<std::string> commandBlock;
    size_t openedDynamicBlockCounter = 0;

    CommandWriter& commandWriter;
};

};
