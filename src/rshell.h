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
    
    queue<Base*> connectorListRecursive;
    queue<Base*> cmdListRecursive;
    queue<Base*> executeListRecursive;
  public:
    rShell() {};
    void display();
    void parse(string);
    Base* recParse(string); //TODO
    void createExecuteList();
    // void createExecuteListRecursive(); // TODO
    void Run();
    
};
#endif
