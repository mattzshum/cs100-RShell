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
        //cout << "HERE" << currentStr << endl;
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

    cout << "After: " << endl; 

    for (int i = 0; i < combined.size(); ++i) {
        cout << combined.at(i) << endl; 
    }

    vector<char*> output(combined.size());
    int size = output.size();
    
    for (int i = 0 ; i < size; ++i) {
       char* temp = new char[combined.at(i).length() + 1];
       strcpy(temp, combined.at(i).c_str());
       output.at(i) = temp;
    }  
    cout << "char* vector: " << endl; 
    for (int i = 0; i < output.size(); ++i){
       cout << output.at(i) << endl;
    }

        for (int i = 0; i < output.size(); i++) {
        //impolement if statments for and and or connectors
            Command* first = new Command(output.at(i));
            //cout << "FIRST" << &first << endl;        
            first->execute();
    }
    return combined;
}

int main() {

    cout << '$' << " ";
    string userInput;
    vector<string> store;
    
    while (true) {
        char userInput[1024];
        // add null termination
        userInput[1023] = '\0';
        cin.getline(userInput, 1024);
        
        store = parseTokenizer(userInput);
        
        }

    
    return 0;
}