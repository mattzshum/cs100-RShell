#ifndef NORMCOMMAND_H
#define NORMCOMMAND_H

#include "command.h"

#include <iostream>

using namespace std;

class normCommand : public Command{
  protected:
    Base* lhs;
    Base* rhs;
  
  public:
    normCommand();
    normCommand(string);
    bool isConnector();
    void setBase(Base*, Base*);
    bool execute(int, int);
    string getCommand();
};

#endif
