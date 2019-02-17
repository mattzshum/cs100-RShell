#include "Command.h"

using namespace std;

Command::Command()
{}

Command::Command(char* input) {
    cmd = input;
    vector<char*> inlist;
    cmdlist = inlist;
}

Command::Command(vector<char*> cmdlist) {
    this->cmdlist = cmdlist;
}

int Command::execute() {
    int status = 0;
    char* args[500];
    for (int i = 0; i < cmdlist.size(); ++i) {
        args[i] = cmdlist.at(i);
    }
    args[cmdlist.size()] = NULL;

    pid_t pid = fork();

    if (pid == -1) {
        perror("Error: fork");
    }

    else if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            status = -1;
            perror("Error: execvp");
            exit(1);
        }
    }
    else {
        int check = 0;
        if (waitpid(pid, &check, 0) == 1) {
            perror("Wait");
        }
        if (WEXITSTATUS(check) != 0) {
            status = -1;
        }
    }
    return status;
}