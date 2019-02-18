#include <iostream>
#include <string>
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
        //cout << "HERE" << currentStr << endl;
        if (currentStr == "&" || currentStr == "|" || currentStr == ";") {
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
            // temp += currentStr + " ";
            combined.push_back(currentStr);
        }
    }

    if (temp.size() > 0) {
        // Get rid of extra space at the end. 
        //cout << temp << '!' << endl;
        if (temp[temp.size() - 1] == ' ') {
            temp.erase(temp.begin() + temp.size()-1);
        }
        //cout << temp << '!' << endl;
        combined.push_back(temp);
    }

    //cout << "After: " << endl; 

    // for (int i = 0; i < combined.size(); ++i) {
    //     cout << combined.at(i) << endl; 
    // }

    // vector<char*> output(combined.size());
    // int size = output.size();
    
    // for (int i = 0 ; i < size; ++i) {
    //    char* temp = new char[combined.at(i).length() + 1];
    //    strcpy(temp, combined.at(i).c_str());
    //    output.at(i) = temp;
    // }  
    // cout << "char* vector: " << endl; 
    // for (int i = 0; i < output.size(); ++i) {
    //    cout << output.at(i) << endl;
    // }

    // for (int i = 0; i < output.size(); i++) {
    //     // Command* left = new Command(output.at(i - 1));
    //     // Command* right = new Command(output.at(i + 1));
    //     // if (output.at(i) == "&&") {
    //     //     if (left->execute()) {
    //     //         right->execute();
    //     //     }
    //     // }
    //     // else if (output.at(i) == "||") {
    //     //     if (!left->execute()) {
    //     //         right->execute();
    //     //     }
    //     // }
    //     // else if (output.at(i) == ";") {
    //     //     left->execute();
    //     //     right->execute();
    //     // }
    //     Command* first = new Command(output.at(i));
    //     //cout << "FIRST" << &first << endl;        
    //     first->execute();
    // }

    return combined;
}

Base* shuntingYard(vector<string> &cmdline) {
    queue<string> cmdQ; 
    stack<string> cmdS;

    for (int i = 0; i < cmdline.size(); ++i) {
        if (cmdline.at(i) != "&" && cmdline.at(i) != "|" && cmdline.at(i) != ";") {
            cmdQ.push(cmdline.at(i));
        }
        else if (cmdline.at(i) == "&" && cmdline.at(i) == "|" && cmdline.at(i) == ";") {
            if (cmdS.empty()) {
                cmdS.push(cmdline.at(i));
                continue;
            }
            cmdS.push(cmdline.at(i));
        }
    }

    while (!cmdS.empty()) {
        cmdQ.push(cmdS.top());
        cmdS.pop();
    }

    stack<Base*> baseS;

    while (!baseS.empty()) {
        baseS.pop();
    }

    Base *order;

    while (!cmdQ.empty()) {
        if (cmdQ.front() == "&") {
            order = new And();
        }
        else if (cmdQ.front() == "|") {
            order = new Or();
        }
        else if (cmdQ.front() == ";") {
            order = new Semi();
        }
        else {
            Base *right = baseS.top();
            baseS.pop();
            Base *left = baseS.top();
            baseS.pop();
            order->set(left, right);
            baseS.push(order);
        }
        cmdQ.pop();
    }

    Base *stpoint = baseS.top();
    while (!baseS.empty()) {
        baseS.pop();
    }

    return stpoint;
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
        char* args[500];
        cmdline = parseTokenizer(userInput);
        //shuntingYard(cmdline);//->execute();

        cout << "HERE" << endl;
        for (int i = 0; i < cmdline.size(); ++i) {
            cout << cmdline.at(i) << endl;
        }

        // for (int i = 0; i < cmdline.size(); ++i) {
        //     args[i] = const_cast<char*>(cmdline.at(i).c_str());
        // }

        // //args[cmdline.size()] = NULL;

        // pid_t pid = fork();

        // if (pid == -1) {
        //     perror("Error: fork");
        // }

        // else if (pid == 0) {
        //     if (execvp(args[0], args) == -1) {
        //         perror("Error: execvp");
        //         exit(1);
        //     }
        // }
        // else {
        //     int check;
        //     if (waitpid(pid, &check, 0) == 1) {
        //         perror("Wait");
        //     }
        //     if (WEXITSTATUS(check) != 0) {
        //         exit(1);
        //     }
        // }
    
        
    }
    
    return 0;
}