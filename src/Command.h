#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "Base.h"
#include <vector>
#include <stack>
#include <queue>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;

class Command : public Base {
    protected:
        char* cmd;
        vector<char*> cmdlist; 
    public:
        Command();
        Command(char* cmd);
        Command(vector<char*> cmdlist);
        virtual int execute();
};

#endif