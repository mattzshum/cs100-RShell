#include "Command.h"

using namespace std;

Command::Command()
{}

Command::Command(char *input) {
    cmd = input;
    vector<char *> inlist;
    inlist.push_back(input);
    inlist.push_back('\0');
    inlist.push_back('\0');
    cmdlist = inlist;
    //cout << "construct char" << endl;
}

Command::Command(vector<char *> cmdlist) {
    this->cmdlist = cmdlist;
        // cout << cmdlist.at(0) << endl;
        // cout << cmdlist.at(1) << endl;
        // cout << "construct vector" << endl;

}

int Command::execute() {
    int status = 1;
    char* args[3];
    args[0] = cmdlist.at(0);
    args[1] = cmdlist.at(1);
    args[2] = (char*)'\0';
    // char *args[2];
    // args[0] = 
    pid_t pid = fork();
    
    // if (!cmd.empty()) {
	// 		cmds.push_back(this->buildCommand(cmd));
	// 	} else if (commands.front() == ";") {
	// 		cmds.push_back(new Terminate()); 
	// 		commands.pop_front();
	// 	} else if (commands.front() == "||") {
	// 		cmds.push_back(new Or()); 
	// 		commands.pop_front();
	// 	} else if (commands.front() == "&&") {
	// 		cmds.push_back(new And());

    if (pid == -1) {
        perror("Error: fork");
    }

    else if (pid == 0) {
        //cout <<  "args[0" << args[0] << endl; 
        if (execvp(args[0], args) == -1) {
            status = 0;
            perror("Error: execvp");
        }
    }
    else {
        int check;
        if (waitpid(pid, &check, 0) == 1) {
            perror("Wait");
        }
        if (WEXITSTATUS(check) != 0) {
            status = 0;
        }
    }
    return status;
}