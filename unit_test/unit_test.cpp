#include "rshell.h"
#include "base.h"
#include "command.h"
#include "connector.h"

#include "and.h"
#include "or.h"
#include "semicolon.h"

#include "normcommand.h"
#include "testcommand.h"

#include "gtest/gtest.h"

#include <iostream>

using namespace std;

TEST(simpleCommand, simpleCommand){
    rShell run;
    string commandLine = "echo A && echo B || ls || ls -a"
    run.parse(commandLine);
    run.createExecuteList();
    EXPECT_EQ(run.Run(), run.Run());
}

TEST(testCommandTrue, testCommandTrue){
    rShell run;
    string commandLine = "test -e main.cpp";
    run.parse(commandLine);
    run.createExecuteList();
    EXPECT_EQ("(True)", run.Run());
}

Test(testCommandFalse, testCommandFalse){
    rShell run;
    string commandLine = "test -e fileDNE.cpp";
    run.parse(commandLine);
    run.createExecuteList();
    EXPECT_EQ("(False)", run.Run());
}

TEST(testCommandBracket, testCommandBracket){
    rShell run;
    string commandLine = "[-e main.cpp]";
    run.parse(commandLine);
    run.createExecuteList();
    EXPECT_EQ("(True)", run.Run());
}

TEST(testFlagF, testFlagF){
    rShell run;
    string commandLine = "test -f main.cpp";
    run.parse(commandLine);
    run.createExecuteList();
    EXPECT_EQ("(True)", run.Run());
}

TEST(testFlagD, testFlagD){
    rShell run;
    string commandLine = "test -d main.cpp";
    run.parse(commandLine);
    run.createExecuteList();
    EXPECT_EQ("(False)", run.Run());
}

TEST(ParenthesisComplex, ParenthesisComplex){
    rShell run;
    string commandLine = "(echo A && echo B) || (echo C && echo D)";
    run.parse(commandLine);
    run.createExecuteList();
    EXPECT_EQ(run.Run(), run.Run());
}


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
