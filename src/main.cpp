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

    //cout << "Before" << endl;
    // uses strtok to get rid of delimiters (chars we want to ignore) 
    while (token != 0) {
        cmdline.push_back(token); //pushes what we want to keep into vector
        //cout << token << endl;
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

    // cout << "After: " << endl; 

    // for (int i = 0; i < combined.size(); ++i) {
    //     cout << combined.at(i) << endl; 
    //     if(cmdline.at(i).size()-1 == ' '){
    //         cmdline.at(i).erase(cmdline.at(i).size()-1);
    //     }
    // }

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
        string input = string(userInput);
        if(input == "exit"){
            exit(1);
        }
        if(input.find("#") != string::npos){
            input = input.substr(0,input.find("#"));
        }
        vector<string> cmdline;
        char* args[2];
        cmdline = parseTokenizer((char*)input.c_str());
        string justCmd;
        string justCmds;
        string restCmds;
        bool OneCmd = false;
        bool hasAnd = false;
        bool hasOr = false;
        bool connected = false;
        for (int i = 0; i < cmdline.size(); ++i) {
            if(cmdline.at(i) == "&&"){
                hasAnd = true;
                //cout << "hasAnd" << endl;
            }
            if(cmdline.at(i) == "||"){
                hasOr = true;
                //cout << "hasOr" << endl;
            }
        }
        int i = 0;
        int status = 1;
        while (i < cmdline.size()) {
            if(cmdline.at(i) == "exit"){
                exit(1);
            }
            if(hasAnd == false && hasOr == false){
                //cout << "why" << endl;
                if(cmdline.at(i) != ";"){
                    if (cmdline.at(i).find(" ") != string::npos) {
                        justCmds = cmdline.at(i).substr(0, cmdline.at(i).find_first_of(" "));
                        restCmds = cmdline.at(i).substr(cmdline.at(i).find_first_of(" ") + 1, cmdline.at(i).length());
                        //cout << "trial" << endl;
                    }
                    else {
                        justCmds = cmdline.at(i);
                        args[0] = (char*)justCmds.c_str();
                        args[1] = (char*)'\0';
                        //cout << "actually her" << endl;
                        //cout << args[0] << endl;
                        //cout << args[1] << endl;
                        OneCmd = true;
                    }
                    if(OneCmd == false){
                        args[0] = (char*)justCmds.c_str();
                        args[1] = (char*)restCmds.c_str();
                        args[2] = (char*)'\0';
                    }
                    OneCmd = false;
                    pid_t pid = fork();
        
                    if (pid == -1) {
                        perror("Error: fork");
                    }
        
                    else if (pid == 0) {
                        if (execvp(args[0], args) == -1) {
                            perror("Error: execvp");
                            status = 0;
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
            
                i++;
            }else if(cmdline.at(i) == "||"){
                if(status == 0){
                    Command* next = new Command((char*)cmdline.at(i+1).c_str());
                    next->execute();
                }
                i = i + 2;
            } else if(cmdline.at(i) == "&&"){
                if(status == 1){
                    Command* next = new Command((char*)cmdline.at(i+1).c_str());
                    next->execute();
                }
                i = i+2;
            } 
            else {
                if(cmdline.size()-1 != i){
                    Command* left = NULL;
                    Command* right = NULL;
                    //cout << "2" << endl;
                    if (cmdline.at(i+1) == "||"){
                        if (cmdline.at(i).find_first_of(" ") != cmdline.at(i).size()-1) {
                            justCmds = cmdline.at(i).substr(0, cmdline.at(i).find_first_of(" "));
                            restCmds = cmdline.at(i).substr(cmdline.at(i).find_first_of(" ") + 1, cmdline.at(i).length());
                            //cout << "justCmds left" << justCmds << endl;
                            vector<char*> input;
                            input.push_back((char*)justCmds.c_str());
                            input.push_back((char*)restCmds.c_str());
                            input.push_back((char*)'\0');
                            left = new Command(input);
                            status = left->execute();
                        } else {
                            // cout << "why here" << endl;
                            cmdline.at(i) = cmdline.at(i).substr(0,cmdline.at(i).size()-1);
                            left = new Command((char*)cmdline.at(i).c_str());
                            status = left->execute();
                        }
                        justCmds = "";
                        restCmds = "";
                        //cout << "second cmd: " << cmdline.at(i+2) << endl;
                        if (cmdline.at(i+2).find(" ") != string::npos) {
                            justCmds = cmdline.at(i + 2).substr(0, cmdline.at(i + 2).find_first_of(" "));
                            restCmds = cmdline.at(i + 2).substr(cmdline.at(i + 2).find_first_of(" ") + 1, cmdline.at(i + 2).length());
                            // cout << "justCmds right: " << justCmds << endl;
                            // cout << "restCmds right: " << restCmds << endl;
                            vector<char*> input2;
                            input2.push_back((char*)justCmds.c_str());
                            input2.push_back((char*)restCmds.c_str());
                            input2.push_back((char*)'\0');
                            right = new Command(input2);
                            if(status == 0){
                                cout << "first command failed execute second: " << endl;
                                right->execute();
                            }
                        } else {
                            right = new Command((char*)cmdline.at(i+2).c_str());
                            if(status == 0){
                                cout << "first command failed execute second: " << endl;
                                right->execute();
                            }
                        }
                        justCmds = "";
                        restCmds = "";
                        //cout << "2.2" << endl;
                        //Or* foo = new Or(left, right);
                        // left->execute();
                        // cout << "2.3" << endl;
                        // right->execute();
                        //cout << "2.4" << endl;
                        connected = true;
                        hasOr = false;
                    }
                   // cout << "broke" << endl;
                    if (cmdline.at(i+1) == "&&"){
                        if (cmdline.at(i).find_first_of(" ") != cmdline.at(i).size()-1) {
                            justCmds = cmdline.at(i).substr(0, cmdline.at(i).find_first_of(" "));
                            restCmds = cmdline.at(i).substr(cmdline.at(i).find_first_of(" ") + 1, cmdline.at(i).length());
                            //cout << "justCmds left" << justCmds << endl;
                            vector<char*> input;
                            input.push_back((char*)justCmds.c_str());
                            input.push_back((char*)restCmds.c_str());
                            input.push_back((char*)'\0');
                            left = new Command(input);
                            
                            status = left->execute();
                        } else {
                            //cout << "why here" << endl;
                            cmdline.at(i) = cmdline.at(i).substr(0,cmdline.at(i).size()-1);
                            if(cmdline.at(i) == "exit"){
                                exit(1);
                            }
                            left = new Command((char*)cmdline.at(i).c_str());
                            status = left->execute();
                        }
                        justCmds = "";
                        restCmds = "";
                        //cout << "second cmd: " << cmdline.at(i+2) << endl;
                        if (cmdline.at(i+2).find(" ") != string::npos) {
                            justCmds = cmdline.at(i + 2).substr(0, cmdline.at(i + 2).find_first_of(" "));
                            restCmds = cmdline.at(i + 2).substr(cmdline.at(i + 2).find_first_of(" ") + 1, cmdline.at(i + 2).length());
                            //cout << "justCmds right: " << justCmds << endl;
                            //cout << "restCmds right: " << restCmds << endl;
                            vector<char*> input2;
                            input2.push_back((char*)justCmds.c_str());
                            input2.push_back((char*)restCmds.c_str());
                            input2.push_back((char*)'\0');
                            right = new Command(input2);
                            if(status == 1){
                                cout << "first command success execute second: " << endl;
                                right->execute();
                            }
                        } else {
                            if(cmdline.at(i+2) == "exit"){
                                exit(1);
                            }
                            //missing if theres a command after
                            if(cmdline.size() - 5 > 0){
                                if(cmdline.at(i+3) == "&&"){
                                    cmdline.at(i+2) = cmdline.at(i+2).substr(0,cmdline.at(i+2).size()-1);
                                }
                            }
                            if(cmdline.at(i) == "exit"){
                                exit(1);
                            }
                            right = new Command((char*)cmdline.at(i+2).c_str());
                             
                             if(status == 1){
                                cout << "first command success execute second: " << endl;
                                right->execute();
                            }
                        }
                        justCmds = "";
                        restCmds = "";
                        //cout << "2.2" << endl;
                        // Or* foo = new Or(left, right);
                        // foo->execute();
                        // cout << "2.3" << endl;
                        // right->execute();
                        //cout << "2.4" << endl;
                        connected = true;
                        hasOr = false;
                    }
                    //cout << "4" << endl;
                    if(connected = false){
                        Command* bar = new Command((char*)cmdline.at(i).c_str());
                        bar->execute();
                    }
                    connected = false;
                    i = i + 3;
                } 
            }
        }
    }
    return 0;
}