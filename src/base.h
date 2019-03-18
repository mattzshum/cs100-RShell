#ifndef BASE_H
#define BASE_H

#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <fstream>

using namespace std;

class Base{
  private: 
    
  public:
    Base() {};
    
    virtual void setBase(Base*, Base*) = 0;
    virtual bool isConnector() = 0;
    virtual string getCommand() = 0;
    virtual bool execute(int, int) = 0;
    
    string cmd;
};

#endif
