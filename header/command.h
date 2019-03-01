#ifndef COMMAND_H
#define COMMAND_H

#include "base.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

/*
Commands are equivalent to Op and Rand from lab3 and lab4. It will execute commands using waitpid, exec, and fork().
Fork will help return the bool value of whether or not the command was succesfully executed or not.
*/

class Command : public Base{
    private:
        //executablel [arg list] [connector] [cmd]
        Base * lhs;
        Base * rhs;
    
    public:
        Command();
        Command(string command);
        bool isConnector();
        void setBase(Base* a, Base* b);
        bool execute();
};

#endif
