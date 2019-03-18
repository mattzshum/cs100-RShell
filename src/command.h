#ifndef COMMAND_H
#define COMMAND_H

#include "base.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Command : public Base{
  protected:
    //executablel [arg list] [connector] [cmd]
    string cmd;
    Base * lhs;
    Base * rhs;
    
  public:
    Command() {
        
    };
    Command(string command) : lhs(0), rhs(0) {
        cmd = command;
    };
    string getCommand() { return cmd; }
    virtual bool isConnector() = 0;
    virtual void setBase(Base*, Base*) = 0;
    virtual bool execute(int, int) = 0;
};
#endif
