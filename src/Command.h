#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "Base.h"
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <cstring>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;

class Command : public Base {
    protected:
        char* cmd;
        int status;
        vector<char*> cmdlist; 
    public:
        Command();
        Command(char* cmd);
        Command(vector<char*> cmdlist);
        int getStatus(){return status;};
        virtual int execute();
};

#endif