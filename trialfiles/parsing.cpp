#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <cstdlib>
#include <stdio.h>

using namespace std;

queue<string> parseCmd(string userInput){
    queue<string> allCmds;
    stack<string> operators;
    int zero = 0;
    int tempInt;
    string tempStr;
    while(userInput.find(" ") != string::npos){
      tempInt = userInput.find(" ");
      tempStr = userInput.substr(0,tempInt);
      if(tempStr == "||" || tempStr == "&&" || tempStr == ";;"){
        operators.push(tempStr);
      } else {
        allCmds.push(tempStr);
      }
      userInput = userInput.substr(tempInt+1,userInput.size()-1);
    }
    tempStr = userInput.substr(0,userInput.size());
    if(tempStr == "||" || tempStr == "&&" || tempStr == ";;"){
       operators.push(tempStr);
    } else {
       allCmds.push(tempStr);
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
    queue<string> outputQ;
   //implement to remvoe anything past a "#" cahracter"
   
   //if the string is more than one arguement
   outputQ = parseCmd(userInput);
   // implement execute outputQ
   cout << outputQ.front() << endl;
   outputQ.pop();
   cout << outputQ.front() << endl;
   outputQ.pop();
      cout << outputQ.front() << endl;
   outputQ.pop();
   cout << outputQ.front() << endl;
   outputQ.pop();
      cout << outputQ.front() << endl;
   outputQ.pop();
   return 0;
}

