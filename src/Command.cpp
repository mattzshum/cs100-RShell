#include "Command.h"

using namespace std;

Command::Command()
{}

Command::Command(char *input) {
    cmd = input;
    vector<char *> inlist;
    // input += '\0'; 
    inlist.push_back(input);
    cmdlist = inlist;
    cout << "construct" << endl;
}

Command::Command(vector<char *> cmdlist) {
    this->cmdlist = cmdlist;
}

int Command::execute() {
    int status = 1;
    char *args[500];
    for (int i = 0; i < cmdlist.size(); ++i) {
        args[i] = cmdlist.at(i);
    }
    pid_t pid = fork();
    if (pid == -1) {
        perror("Error: fork");
    }

    else if (pid == 0)
    {
        if (execvp(this->cmd, args) == -1)
        {
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