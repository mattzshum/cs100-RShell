#ifndef TESTCOMMAND_H
#define TESTCOMMAND_H

#include "command.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class TestCommand : public Command{
  protected:
    Base *lhs;
    Base *rhs;
  public:
    TestCommand();
    TestCommand(string);
    void setBase(Base*, Base*);
    bool isConnector();
    bool execute();
};

#endif
