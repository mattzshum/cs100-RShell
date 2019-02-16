#include <iostream>
#include <string>
#include <queue>
#include <cstring>
#include <stack>
#include <cstdlib>
#include <stdio.h>

using namespace std;

queue<char*> parseCmd(string input){
    queue<char*> allCmds;
    stack<char*> operators;
    int zero = 0;
    int tempInt;
    char *charStr;
    string userInput = input;
    string tempStr;
    cout << "fucntion testing each parse:" << endl;
    while(userInput.find(" ") != string::npos){
      tempInt = userInput.find(" ");
      tempStr = userInput.substr(0,tempInt);
      strcpy(charStr,tempStr.c_str());
      if(tempStr == "||" || tempStr == "&&" || tempStr == ";;"){
        operators.push(charStr);
      } else {
        allCmds.push(charStr);
        cout << charStr << endl;
      }
      userInput = userInput.substr(tempInt+1,userInput.size()-1);
    }
    tempStr = userInput.substr(0,userInput.size());
    strcpy(charStr,tempStr.c_str());
    if(tempStr == "||" || tempStr == "&&" || tempStr == ";;"){
       operators.push(charStr);
    } else {
       allCmds.push(charStr);
              cout << charStr <<endl;
    }
    while(!operators.empty()){
        allCmds.push(operators.top());
        operators.pop();
    }
    return allCmds;
}

int main(){
    string userInput;
    getline(cin, userInput);
    queue<char*> outputQ;
    
   //implement to remvoe anything past a "#" cahracter"
   
   //if the string is more than one arguement
   outputQ = parseCmd(userInput);
   // implement execute outputQ
   cout << "now calling from the main:" << endl;
   cout << outputQ.front() << endl;
   outputQ.pop();
   cout << outputQ.front() << endl;
   outputQ.pop();
      cout << outputQ.front() << endl;
    outputQ.pop();
//   cout << outputQ.front() << endl;
//   outputQ.pop();
//       cout << outputQ.front() << endl;
//   outputQ.pop();
   return 0;
}

