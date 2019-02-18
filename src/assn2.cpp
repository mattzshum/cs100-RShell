#include <iostream>
#include <string>
#include <queue>
#include <cstring>
#include <stack>
#include <cstdlib>
#include <stdio.h>
#include <algorithm>
#include "command.h"
#include "Base.h"

using namespace std;

void parseCmd(string input, vector<string> &allCmds, vector<string> &operators){
    int zero = 0;
    int tempInt;
    bool tookLoop = false;
    bool isCmd = true;
   // char *charStr;
    if(input.find("#") != string::npos){
        int comment = input.find("#");
        input = input.substr(0,comment);
    }
    string userInput = input;
    string tempStr;
    string addString = "";
    //cout << "fucntion testing each parse:" << endl;
    while(userInput.find(" ") != string::npos){
      tookLoop = true;
      tempInt = userInput.find(" ");
      tempStr = userInput.substr(0,tempInt);
      
      
    //   if((userInput.substr(tempInt+1,2) == ";;") || (userInput.substr(tempInt+1,2) == "||")  || (userInput.substr(tempInt+1,2) == "&&") ){
    //       isCmd = false;
    //       cout << "isCmd: false" << endl;
    //       cout << "substr: " << userInput.substr(tempInt+1,2) << endl;
    //       cout << userInput.at(tempInt+1) << endl;
    //       cout << userInput.at(tempInt+2) << endl;
    //   } else {
    //       cout << "cmd" << endl;
    //   }
       
      
      if(tempStr == "||" || tempStr == "&&" || tempStr == ";;"){
        allCmds.push_back(addString);
        isCmd = false;
        addString = "";
        operators.push_back(tempStr);
        //cout << "operators push :" << tempStr << endl;
      } else if (isCmd = true){
        if(addString == ""){
            addString = addString + tempStr;
        } else {
            addString = addString + " " + tempStr;
        }
        //cout << "addString: " << addString << endl;
      } else {
          isCmd = true;
        tempStr = addString + tempStr;
        allCmds.push_back(tempStr);
        addString = "";
        //cout << "tempStr: " << tempStr << endl;
      }
      userInput = userInput.substr(tempInt+1,userInput.size()-1);
      isCmd = true;
    }
    tempStr = userInput.substr(0,userInput.size());
    if (addString != ""){
        tempStr = addString + " " + tempStr;
    }
    allCmds.push_back(tempStr);
    addString = "";
    //cout << "tempStr2: " << tempStr << endl;
    //cout << "opertaror top: " << operators.top() << endl;
    // while(!operators.empty()){
    //     allCmds.push(operators.top());
    //     operators.pop();
    // }
    return;
}

int main(){
    string userInput;
    getline(cin, userInput);
    vector<string> outputQ;
    vector<string> ops;
    
   //implement to remvoe anything past a "#" cahracter"

   //if the string is more than one arguement
    parseCmd(userInput, outputQ, ops);
    vector<char*> charOut(outputQ.size());
   int size = outputQ.size();
   for (int i =0 ; i < size; i++){
       
       char* temp = new char[outputQ.at(i).length() + 1];
       strcpy(temp, outputQ.at(i).c_str());
       charOut.at(i) = temp;
   }  
 for (int i = 0; i < charOut.size();i++){
     cout << charOut.at(i) << endl;
 }
  Command* first = new Command(charOut);

  first->execute();
   // implement execute outputQ
   //cout << "now calling from the main:" << endl;
   
   return 0;
}

