#pragma once

#include <string>
#include <vector>

namespace Homework {

class CommandWriter {
public:
    virtual ~CommandWriter() {
    }

    virtual void write(const std::vector<std::string>& commands) const {
        //the default implementation does nothing
    }

};

};
