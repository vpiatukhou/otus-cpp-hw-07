#include "CommandProcessor.h"
#include "gmock/gmock.h"

using namespace Homework;
using namespace std;
using ::testing::_;

const size_t BLOCK_SIZE = 3;

class CommandWriterMock : public CommandWriter {
public:
    MOCK_METHOD(void, write, (const vector<string>& commands), (const, override));
};

TEST(commandProcessorTest, staticCommandBlock) {
    //given
    CommandWriterMock commandWriter;
    CommandProcessor commandProcessor(commandWriter, BLOCK_SIZE);

    vector<string> block1 = { "cmd1", "cmd2", "cmd3" };
    vector<string> block2 = { "cmd4", "cmd5", "cmd6" };
    vector<string> block3 = { "cmd7", "cmd8" };

    //expect
    EXPECT_CALL(commandWriter, write(block1));
    EXPECT_CALL(commandWriter, write(block2));
    EXPECT_CALL(commandWriter, write(block3)).Times(0);

    //when
    for (auto& command : block1) {
        commandProcessor.process(command);
    }
    for (auto& command : block2) {
        commandProcessor.process(command);
    }
    for (auto& command : block3) {
        commandProcessor.process(command);
    }
}

TEST(commandProcessorTest, flushNoCommands) {
    //given
    CommandWriterMock commandWriter;
    CommandProcessor commandProcessor(commandWriter, BLOCK_SIZE);

    //expect
    EXPECT_CALL(commandWriter, write(_)).Times(0);

    //when
    commandProcessor.flush();
}

TEST(commandProcessorTest, flush) {
    //given
    CommandWriterMock commandWriter;
    CommandProcessor commandProcessor(commandWriter, BLOCK_SIZE);

    vector<string> block = { "cmd1", "cmd2" };

    //expect
    EXPECT_CALL(commandWriter, write(block));

    //when
    for (auto& command : block) {
        commandProcessor.process(command);
    }
    commandProcessor.flush();
}

TEST(commandProcessorTest, flushOpenedDynamicBlock) {
    //given
    CommandWriterMock commandWriter;
    CommandProcessor commandProcessor(commandWriter, BLOCK_SIZE);

    //expect
    EXPECT_CALL(commandWriter, write(_)).Times(0);

    //when
    commandProcessor.process("{");
    commandProcessor.process("cmd1");
    commandProcessor.process("cmd2");
    commandProcessor.flush();
}

TEST(commandProcessorTest, nestedDynamicBlock) {
    //given
    CommandWriterMock commandWriter;
    CommandProcessor commandProcessor(commandWriter, BLOCK_SIZE);

    //expect
    vector<string> block = { "cmd1", "cmd2", "cmd3", "cmd4", "cmd5" };

    EXPECT_CALL(commandWriter, write(block));

    //when
    commandProcessor.process("{");
    commandProcessor.process("cmd1");
    commandProcessor.process("cmd2");
    commandProcessor.process("{");
    commandProcessor.process("cmd3");
    commandProcessor.process("cmd4");
    commandProcessor.process("}");
    commandProcessor.process("cmd5");
    commandProcessor.process("}");
}

TEST(commandProcessorTest, complexTest) {
    //given
    CommandWriterMock commandWriter;
    CommandProcessor commandProcessor(commandWriter, BLOCK_SIZE);

    //expect
    std::vector<std::string> block1 = { "cmd1", "cmd2" };
    std::vector<std::string> block2 = { "cmd3", "cmd4" };
    std::vector<std::string> block3 = { "cmd5", "cmd6", "cmd7", "cmd8", "cmd9" };

    EXPECT_CALL(commandWriter, write(block1));
    EXPECT_CALL(commandWriter, write(block2));
    EXPECT_CALL(commandWriter, write(block3));

    //when
    commandProcessor.process("cmd1");
    commandProcessor.process("cmd2");
    commandProcessor.process("{");
    commandProcessor.process("cmd3");
    commandProcessor.process("cmd4");
    commandProcessor.process("}");
    commandProcessor.process("{");
    commandProcessor.process("cmd5");
    commandProcessor.process("cmd6");
    commandProcessor.process("{");
    commandProcessor.process("cmd7");
    commandProcessor.process("cmd8");
    commandProcessor.process("}");
    commandProcessor.process("cmd9");
    commandProcessor.process("}");
    commandProcessor.process("{");
    commandProcessor.process("cmd10");
    commandProcessor.process("cmd11");
    commandProcessor.flush();
}
