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

using namespace std;

void parseTokenizer(char *str) {
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

    vector<char*> output(combined.size());
    for (int i = 0; i < output.size(); ++i) {
        char* temp = new char[combined.at(i).length() + 1];
        strcpy(temp, combined.at(i).c_str());
        output.at(i) = temp;
    }

    cout << "char* vector: " << endl; 
    for (int i = 0; i < output.size(); ++i){
       cout << output.at(i) << endl;
    }

    for (int i = 0; i < output.size(); ++i) {
        Command* cmd = new Command(output.at(i));
        cmd->execute();
    }
}

int main(int argc, char** argv) {

    cout << '$' << " ";
    string userInput;

    while (true) {
        char userInput[1024];
        cin.getline(userInput, 1024);
        parseTokenizer(userInput);
    }

    
    return 0;
}
