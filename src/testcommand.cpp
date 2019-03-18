#include "testcommand.h"

using namespace std;

TestCommand::TestCommand(){}

TestCommand::TestCommand(string command) : lhs(0), rhs(0){
    cmd = command;
}

void TestCommand::setBase(Base* a, Base* b){
    lhs = a;
    rhs = b;
}

bool TestCommand::isConnector(){
    return false;
}

string TestCommand::getCommand() { return cmd;}

bool TestCommand::execute(int in, int out){
    
    char ** path;
    int argc = 0;
        
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
        restCmd = temp;
        //cout << "string check: " << temp << endl;
        
        if (temp != "") {
            string restCmd = cmd.substr(cmd.find_first_of(" "), cmd.length());
            restCmd.erase(0, 1); 
            path = new char*[2];
            path[0] = (char*)cmdSysCall.c_str();
            path[1] = (char*)restCmd.c_str();
            path[2] = NULL;
            argc = 2;
        }
        else {
            path = new char*[1];
            path[0] = (char*)cmdSysCall.c_str();
            path[1] = NULL;
            argc = 2;
        }
        
        if(path[1] == NULL){
            cout << "Error with loading path" << endl;
        }
        
    struct stat buf;
    
    if (argc != 2) {
        return false;
    }
    
    //cout << "TESTER" << endl;
    
    if (stat(path[1], &buf) == -1) {
        perror("stat");
        cout << "(False)" << endl;
        return false;
    }
    else if(cmdSysCall == "-e"){
        cout << "(TRUE)" << endl;
        return true;
    }
    
    switch (buf.st_mode & S_IFMT) {
        case S_IFDIR:  
            if (cmdSysCall == "-d") {
                cout << "(True)" << endl;            
                return true;
            }
            
        case S_IFREG:
            if(cmdSysCall == "-f") {
                cout << "(True)" << endl;
                return true;
            }
            
        default:
            cout << "(False)" << endl;
            return false;
    }
    cout << "(False)" << endl;    return false;
}
