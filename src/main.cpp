#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <iterator>
#include <queue>
#include <cstring>
#include <stack>
#include <cstdlib>
#include <stdio.h>
#include <algorithm>
#include "Command.h"
#include "Base.h"
#include "Connector.h"
#include "And.h"
#include "Or.h"
#include "Semi.h"

using namespace std;

vector<string> parseTokenizer(char *str) {
    char *token;
    //cout << "Check:" << endl;
    token = strtok(str, " ,.");
    // cout << token << endl;
    vector<string> cmdline;

    cout << "Before" << endl;
    // uses strtok to get rid of delimiters (chars we want to ignore) 
    while (token != 0) {
        cmdline.push_back(token); //pushes what we want to keep into vector
        cout << token << endl;
        token = strtok(0, " ,.");
    }
    // cmdline vector is now filled with our "simplified" commands

    // create another vector to put everything before a connector as full command
    vector<string> combined;
    string temp = "";
    string semicolon = "";
    for (int i = 0; i < cmdline.size(); ++i) {
        string currentStr = cmdline[i];
        if (currentStr == "&&" || currentStr == "||" || currentStr == ";") {
            combined.push_back(temp);
            temp = "";
            combined.push_back(currentStr);
        }
        else if (currentStr[currentStr.size() - 1] == ';') {
            currentStr.erase(currentStr.begin() + currentStr.size()-1);
            temp += currentStr;
            combined.push_back(temp);
            combined.push_back(";");
            temp = "";
        }
        else {
            temp += currentStr + " ";
        }
    }

    if (temp.size() > 0) {
        if (temp[temp.size() - 1] == ' ') {
            temp.erase(temp.begin() + temp.size() - 1);
        }
        combined.push_back(temp);
    }

    cout << "After: " << endl; 

    for (int i = 0; i < combined.size(); ++i) {
        cout << combined.at(i) << endl; 
    }

    return combined;
}

int main() {
    string userInput;
    vector<string> store;
    
    while (true) {
        cout << '$' << " ";
        char userInput[1024];
        userInput[1023] = '\0';
        cin.getline(userInput, 1024);
        vector<string> cmdline;
        char* args[1];
        cmdline = parseTokenizer(userInput);
        string justCmds;
        string restCmds;
        bool oneCmd = false;
        
        for (int i = 0; i < cmdline.size(); ++i) {
            if (cmdline.at(i).find(" ") != string::npos) {
                justCmds = cmdline.at(i).substr(0, cmdline.at(i).find_first_of(" "));
                restCmds = cmdline.at(i).substr(cmdline.at(i).find_first_of(" ") + 1, cmdline.at(i).length());
            }
            else {
                justCmds = cmdline.at(i);
                args[0] = (char*)justCmds.c_str();
                args[1] =  (char*)'\0';
                oneCmd = true;
            }
        }

        if (oneCmd == false) {
            args[0] = (char*)justCmds.c_str();
            args[1] = (char*)restCmds.c_str();
        }

        pid_t pid = fork();

        if (pid == -1) {
            perror("Error: fork");
        }

        else if (pid == 0) {
            if (execvp(args[0], args) == -1) {
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
                exit(1);
            }
        }
    
        
    }
    
    return 0;
}