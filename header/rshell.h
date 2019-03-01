#ifndef RSHELL_H
#define RSHELL_H

#include <string>
#include <vector>
#include "base.h"
#include <queue>

using namespace std;

class rShell{
    private:
        queue<Base*> connectorlist;
        queue<Base*> cmdlist;
        queue<Base*> executeList;
        
    public:
        rShell() {};
        void display();
        void parse(string);
        void createExecuteList();
        void Run();
};

#endif
