#include "../src/base.h"
#include "../src/command.h"
#include "../src/connector.h"

#include "../src/and.h"
#include "../src/or.h"
#include "../src/semicolon.h"

#include "../src/normcommand.h"
#include "../src/testcommand.h"

#include "../src/rshell.h"
#include "../src/doubleoutput.h"
#include "../src/outputredirect.h"
#include "../src/inputredirect.h"

#include "gtest/gtest.h"

#include <iostream>

using namespace std;

TEST(simpleCommand, simpleCommand){
    Base* lhs  = new normCommand("echo A");
    Base* rhs = new normCommand("echo B");
    Base* connector = new And();
    connector->setBase(lhs, rhs);
    EXPECT_EQ(connector->execute(0, 0),connector->execute(0, 0) );
}

TEST(testCommandTrue, testCommandTrue){
    string commandLine = "test -e main.cpp";
    Base* lhs = new TestCommand(commandLine);
    EXPECT_EQ(lhs->execute(0, 0), lhs->execute(0, 0));
}

TEST(testCommandTrue, testCommandTrue2){
    string commandLine = "test -e rshell.cpp";
    Base* lhs = new TestCommand(commandLine);
    EXPECT_EQ(lhs->execute(0, 0), lhs->execute(0, 0));
}

TEST(testCommandTrue, testCommandTrue3){
    string commandLine = "test -e command.h";
    Base* lhs = new TestCommand(commandLine);
    EXPECT_EQ(lhs->execute(0, 0), lhs->execute(0, 0));
}

TEST(testCommandTrue, testCommandTrue4){
    string commandLine = "test -e and.h";
    Base* lhs = new TestCommand(commandLine);
    EXPECT_EQ(lhs->execute(0, 0), lhs->execute(0, 0));
}

TEST(testCommandTrue, testCommandTrue5){
    string commandLine = "test -e or.h";
    Base* lhs = new TestCommand(commandLine);
    EXPECT_EQ(lhs->execute(0, 0), lhs->execute(0, 0));
}

TEST(testCommandFalse, testCommandFalse){
    string falseTest = "test -e false.cpp";
    Base* lhs = new TestCommand(falseTest);
    EXPECT_EQ(lhs->execute(0, 0), lhs->execute(0, 0));
}

TEST(testCommandFalse, testCommandFalse2){
    string falseTest = "test -e fake.cpp";
    Base* lhs = new TestCommand(falseTest);
    EXPECT_EQ(lhs->execute(0, 0), lhs->execute(0, 0));
}

TEST(testCommandFalse, testCommandFalse3){
    string falseTest = "test -e dob.cpp";
    Base* lhs = new TestCommand(falseTest);
    EXPECT_EQ(lhs->execute(0, 0), lhs->execute(0, 0));
}

TEST(testCommandFalse, testCommandFalse4){
    string falseTest = "test -e bob.cpp";
    Base* lhs = new TestCommand(falseTest);
    EXPECT_EQ(lhs->execute(0, 0), lhs->execute(0, 0));
}

TEST(testCommandFalse, testCommandFalse5){
    string falseTest = "test -e whack.cpp";
    Base* lhs = new TestCommand(falseTest);
    EXPECT_EQ(lhs->execute(0, 0), lhs->execute(0, 0));
}

TEST(testCommandBracket, testCommandBracket){
    string commandLine = "[-e main.cpp]";
    Base* lhs = new TestCommand(commandLine);
    EXPECT_EQ(lhs->execute(0, 0), lhs->execute(0, 0));
}

TEST(testCommandBracket, testCommandBracket2){
    string commandLine = "[-e and.h]";
    Base* lhs = new TestCommand(commandLine);
    EXPECT_EQ(lhs->execute(0, 0), lhs->execute(0, 0));
}

TEST(testCommandBracket, testCommandBracket3){
    string commandLine = "[-e rshell.cpp]";
    Base* lhs = new TestCommand(commandLine);
    EXPECT_EQ(lhs->execute(0, 0), lhs->execute(0, 0));
}

TEST(testCommandBracket, testCommandBracket4){
    string commandLine = "[-e normcommand.cpp]";
    Base* lhs = new TestCommand(commandLine);
    EXPECT_EQ(lhs->execute(0, 0), lhs->execute(0, 0));
}

TEST(testCommandBracket, testCommandBracket5){
    string commandLine = "[-e testcommand.cpp]";
    Base* lhs = new TestCommand(commandLine);
    EXPECT_EQ(lhs->execute(0, 0), lhs->execute(0, 0));
}

TEST(testFlagF, testFlagF){
    string commandLine = "test -f main.cpp";
    Base* lhs = new TestCommand(commandLine);
    EXPECT_EQ(lhs->execute(0, 0), lhs->execute(0, 0));
}

TEST(testFlagF, testFlagF2){
    string commandLine = "test -f rshell.cpp";
    Base* lhs = new TestCommand(commandLine);
    EXPECT_EQ(lhs->execute(0, 0), lhs->execute(0, 0));
}


TEST(testFlagD, testFlagD){
    string commandLine = "test -d main.cpp";
    Base* lhs = new TestCommand(commandLine);
    EXPECT_EQ(lhs->execute(0, 0), lhs->execute(0, 0));
}

TEST(ParenthesisComplex, ParenthesisComplex){
    string commandLine = "(echo A && echo B) || (echo C && echo D)";
    Base* oneLhs = new normCommand("echo A");
    Base* oneRhs = new normCommand("echo B");
    Base* twoLhs = new normCommand("echo C");
    Base* twoRhs = new normCommand("echo D");
    
    Base* connectorOne = new And();
    connectorOne->setBase(oneLhs, oneRhs);
    Base* connectorTwo = new And();
    connectorTwo->setBase(twoLhs, twoRhs);
    Base* overallConnector = new Or();
    overallConnector->setBase(connectorOne, connectorTwo);
    EXPECT_EQ(overallConnector->execute(0, 0), overallConnector->execute(0, 0));
}

TEST(carrotRight, carrotDoubleRight){
    string commandLine = "ls -a >> existingInputFile.txt";
    Base* connector = new DoubleOutput();
    Base* lhs = new normCommand("ls -a");
    Base* rhs = new normCommand("existingInputFile.txt");
    
    connector->setBase(lhs, rhs);
    EXPECT_EQ(connector->execute(0,0), connector->execute(0,0));
}

TEST(carrotLeft, carrotLeftSingle){
    string commandLine = "existingInputFile.txt < ls -a";
    Base* connector = new InputRedirect();
    Base* lhs = new normCommand("existingInputFile.txt");
    Base* rhs = new normCommand("ls -a");

    connector->setBase(lhs, rhs);
    EXPECT_EQ(connector->execute(0,0), connector->execute(0,0));
}

TEST(carrotRightSingle, carrotRightSingle){
    string commandLine = "ls -a > existingInputFile.txt";
    Base* connector = new OutputRedirect();
    Base* lhs = new normCommand("ls -a");
    Base* rhs = new normCommand("existingInputFile.txt");
    
    connector->setBase(lhs, rhs);
    EXPECT_EQ(connector->execute(0,0), connector->execute(0,0));
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
