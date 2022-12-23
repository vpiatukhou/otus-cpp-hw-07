#pragma once

#include "CommandWriter.h"
#include <string>
#include <vector>
#include <ostream>

namespace Homework {

class CommandWriterImpl : public CommandWriter {
public:
    void write(const std::vector<std::string>& commands) const override;
private:
    void writeToStream(std::ostream& ostream, const std::vector<std::string>& commands) const;
    void writeToFile(const std::vector<std::string>& commands) const;

};

};
