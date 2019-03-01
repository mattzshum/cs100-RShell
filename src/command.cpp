#include "../header/command.h"

using namespace std;

Command::Command() {};

Command::Command(string command) : lhs(0), rhs(0) {
    cmd = command;
}
    
bool Command::isConnector() {
    return false; 
}
    
void Command::setBase(Base* a, Base* b) {
    lhs = a;
    rhs = b;
}
    
bool Command::execute() {
    char ** args;    
    istringstream iss(cmd);
    string temp = "";
    string cmdSysCall;
    string restCmd;
        
    iss >> temp;
    cmdSysCall = temp;
        
    if (cmdSysCall == "exit") {
        exit(1);
    }
        
    temp = "";
    iss >> temp;

    if (temp != "") {            
        string restCmd = cmd.substr(cmd.find_first_of(" "), cmd.length()); // check the syntax of this 
        restCmd.erase(0, 1); 
        args = new char*[2];
        args[0] = (char*)cmdSysCall.c_str();
        args[1] = (char*)restCmd.c_str();
        args[2] = NULL;
    }

    else {
        args = new char*[1];
        args[0] = (char*)cmdSysCall.c_str();
        args[1] = NULL;            
    }
    
    pid_t pid = fork();
        
    if (pid > 0) {
        int Status;
            
        if (waitpid(pid, &Status, 0) == -1){       
            perror("wait");
        }
            
        if (WEXITSTATUS(Status) != 0) {
            return false;
        }
    }
        
    else if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("exec");
            exit(EXIT_FAILURE);
        }
    }

    else{
        perror("fork");
        return false;
    }

    return true;
}
