#include "rshell.h"
#include "and.h"
#include "base.h"
#include "command.h"
#include "connector.h"
#include "normcommand.h"
#include "testcommand.h"
#include "or.h"
#include "semicolon.h"

#include "gtest/gtest.h"

#include <iostream>

using namespace std;

int main(){
    rShell run;
    string commandLine;
    while(commandLine != "exit"){
        run.display();
        getline(cin, commandLine);
        cout << endl;
        if(commandLine == "exit"){
            break;
        }
        run.parse(commandLine);
        run.createExecuteList();
        run.Run();
    }
    
    return 0;
}
