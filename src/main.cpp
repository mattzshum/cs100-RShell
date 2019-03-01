#include <iostream>

#include "../header/rshell.h"

using namespace std;

int main() {
    rShell run;
    string commandLine;
    while (commandLine != "exit") {
        run.display();
        getline(cin, commandLine);
        cout << endl;
        if (commandLine == "exit") {
            break;
        }
        run.parse(commandLine);
        run.createExecuteList();
        run.Run();
    }
    
    return 0;
}
