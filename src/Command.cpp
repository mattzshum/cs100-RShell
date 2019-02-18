#include "Command.h"

using namespace std;

Command::Command()
{}

Command::Command(char *input) {
    cmd = input;
    vector<char *> inlist;
    input += '\0'; 
    inlist.push_back(input);
    cmdlist = inlist;
    cout << "construct" << endl;
}

Command::Command(vector<char *> cmdlist) {
    this->cmdlist = cmdlist;
        //cout << "construct" << endl;

}

int Command::execute() {
    int status = 1;
    char *args[500];
    for (int i = 0; i < cmdlist.size(); ++i) {
        args[i] = cmdlist.at(i);
    }

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
        if (execvp(args[0], args) == -1) {
            status = 0;
            perror("Error: execvp");
            exit(1);
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