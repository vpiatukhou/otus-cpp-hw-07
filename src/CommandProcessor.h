#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace Homework {

	class CommandProcessor {

	public:
		CommandProcessor(std::size_t blockSize_) : blockSize(blockSize_) {
		}

		void process(const std::string& command);

	private:
		std::size_t blockSize;
		std::vector<std::string> commandBlock;
	};

};
