#include <boost/tokenizer.hpp>
#include <string>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <iostream>
#include <stdio.h>
#include <iostream>
#include <vector>

#include "rshell.h"

#include "or.h"
#include "semicolon.h"
#include "and.h"
#include "connector.h"
#include "command.h"
#include "testcommand.h"
#include "normcommand.h"

using namespace std;
using namespace boost;

void rShell::display(){
    cout << "$ ";
}

Base* rShell::recParse(string internalCommand) { //TODO
    typedef tokenizer<char_separator<char> > tokenizer;
    char_separator<char> split("", "&;|#()", drop_empty_tokens);
    tokenizer tokens(internalCommand, split);
    for(tokenizer::iterator tok = tokens.begin(); tok != tokens.end(); ++tok){
        if(*(tok) == "#"){
            break;
        }
        else if(*(tok) == "("){
            string internalCmd;
            tok++;
            while(*(tok) != ")"){
                internalCmd += *(tok);
                tok++;
            }
            cmdlist.push(recParse(internalCmd));
        }
        else if(*(tok) == "|"){
            tok++; 
            //| always comes in pairs so must ++ to skip iteration
            
            Base* oor = new Or();
            connectorListRecursive.push(oor);
        }
        else if(*(tok) == "&"){
            tok++;
            
            Base* aand = new And();
            connectorListRecursive.push(aand);
        }
        else if(*(tok) == ";"){
            //do not need to skip, ; only has one iter
            
            Base* semicolon = new SemiColon();
            connectorListRecursive.push(semicolon);
        }
        else{
            //cout << "has arrived at an unexpected point" << endl;
            string toker = *(tok);
            while(toker.at(0) == ' '){ 
                // this is to remove extra whitespaces
                toker.erase(toker.begin());
                if(toker == ""){
                    break;
                }
            }
            //this is where we should create test and norm commands
            if(toker != ""){
                while(toker.at(toker.size()-1) == ' '){
                    toker.erase(toker.end()-1);
                    toker.resize(toker.size());
                }
            }
            
            stringstream ss;
            ss << toker;    //check
            
            string determString;
            ss >> determString;
            
            string tempHolder;
            
            if (determString == "[" || determString == "test") {
                //cout << "CREATING TESTCOMMAND" << endl;
                string finalString;
                ss >> finalString;
                //cout << "first finString check" << finalString << endl;
                if (finalString.size() == 2) {
                    ss >> tempHolder;
                    finalString += " " + tempHolder;
                    //cout << "second finString check: " << finalString << endl;
                }
                else{
                    string tempFinString = "-e " + finalString;
                    finalString = tempFinString;
                }
                //cout << "finalString Check: " << finalString << endl;
                Command* testcmd = new TestCommand(finalString);
                cmdListRecursive.push(testcmd);
            }
    
            else{
                //cout << "CREATING NORMAL COMMAND" << endl;
                if(toker != ""){
                    normCommand* comnd = new normCommand(toker);
                    cmdListRecursive.push(comnd);
                }
            }
        }
    }
    Base* returnConnector = connectorListRecursive.front();
    connectorListRecursive.pop();
    Base* lhs = cmdListRecursive.front();
    cmdListRecursive.pop();
    Base* rhs = cmdListRecursive.front();
    cmdListRecursive.pop();
    returnConnector->setBase(lhs, rhs);
    return returnConnector;
}

void rShell::parse(string cmdLine){
    typedef tokenizer<char_separator<char> > tokenizer;
    char_separator<char> split("", "&;|#()", drop_empty_tokens);
    tokenizer tokens(cmdLine, split);
    for(tokenizer::iterator tok = tokens.begin(); tok != tokens.end(); ++tok){
        //cout << "Beginning parse iter again" << endl;
        // << *(tok) << endl;
        if (*(tok) == "#") {
            break;
        }
        
        // cout << "CHECK PARENTHESES" << endl;
        
        //CHECK FOR PARENTHESES
        else if(*(tok) == "("){
            string internalCmd;
            tok++;
            while(*(tok) != ")"){
                internalCmd += *(tok);
                tok++;
            }
            cmdlist.push(recParse(internalCmd));
        }
        
        
        else if(*(tok) == "|"){
            tok++; 
            //| always comes in pairs so must ++ to skip iteration 
            
            Base* oor = new Or();
            connectorlist.push(oor);
        }
        else if(*(tok) == "&"){
            tok++;
            Base* aand = new And();
            connectorlist.push(aand);
        }
        else if(*(tok) == ";"){
            //do not need to skip, ; only has one iter
            
            Base* semicolon = new SemiColon();
            connectorlist.push(semicolon);#include <boost/tokenizer.hpp>
#include <string>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <iostream>
#include <stdio.h>
#include <iostream>
#include <vector>

#include "rshell.h"

#include "or.h"
#include "semicolon.h"
#include "and.h"
#include "connector.h"
#include "command.h"
#include "testcommand.h"
#include "normcommand.h"

using namespace std;
using namespace boost;

void rShell::display(){
    cout << "$ ";
}

Base* rShell::recParse(string internalCommand) { //TODO
    typedef tokenizer<char_separator<char> > tokenizer;
    char_separator<char> split("", "&;|#()", drop_empty_tokens);
    tokenizer tokens(internalCommand, split);
    for(tokenizer::iterator tok = tokens.begin(); tok != tokens.end(); ++tok){
        if(*(tok) == "#"){
            break;
        }
        else if(*(tok) == "("){
            string internalCmd;
            tok++;
            while(*(tok) != ")"){
                internalCmd += *(tok);
                tok++;
            }
            cmdlist.push(recParse(internalCmd));
        }
        else if(*(tok) == "|"){
            tok++; 
            //| always comes in pairs so must ++ to skip iteration
            
            Base* oor = new Or();
            connectorListRecursive.push(oor);
        }
        else if(*(tok) == "&"){
            tok++;
            
            Base* aand = new And();
            connectorListRecursive.push(aand);
        }
        else if(*(tok) == ";"){
            //do not need to skip, ; only has one iter
            
            Base* semicolon = new SemiColon();
            connectorListRecursive.push(semicolon);
        }
        else{
            //cout << "has arrived at an unexpected point" << endl;
            string toker = *(tok);
            while(toker.at(0) == ' '){ 
                // this is to remove extra whitespaces
                toker.erase(toker.begin());
                if(toker == ""){
                    break;
                }
            }
            //this is where we should create test and norm commands
            if(toker != ""){
                while(toker.at(toker.size()-1) == ' '){
                    toker.erase(toker.end()-1);
                    toker.resize(toker.size());
                }
            }
            
            stringstream ss;
            ss << toker;    //check
            
            string determString;
            ss >> determString;
            
            string tempHolder;
            
            if (determString == "[" || determString == "test") {
                //cout << "CREATING TESTCOMMAND" << endl;
                string finalString;
                ss >> finalString;
                //cout << "first finString check" << finalString << endl;
                if (finalString.size() == 2) {
                    ss >> tempHolder;
                    finalString += " " + tempHolder;
                    //cout << "second finString check: " << finalString << endl;
                }
                else{
                    string tempFinString = "-e " + finalString;
                    finalString = tempFinString;
                }
                //cout << "finalString Check: " << finalString << endl;
                Command* testcmd = new TestCommand(finalString);
                cmdListRecursive.push(testcmd);
            }
    
            else{
                //cout << "CREATING NORMAL COMMAND" << endl;
                if(toker != ""){
                    normCommand* comnd = new normCommand(toker);
                    cmdListRecursive.push(comnd);
                }
            }
        }
    }
    Base* returnConnector = connectorListRecursive.front();
    connectorListRecursive.pop();
    Base* lhs = cmdListRecursive.front();
    cmdListRecursive.pop();
    Base* rhs = cmdListRecursive.front();
    cmdListRecursive.pop();
    returnConnector->setBase(lhs, rhs);
    return returnConnector;
}

void rShell::parse(string cmdLine){
    typedef tokenizer<char_separator<char> > tokenizer;
    char_separator<char> split("", "&;|#()", drop_empty_tokens);
    tokenizer tokens(cmdLine, split);
    for(tokenizer::iterator tok = tokens.begin(); tok != tokens.end(); ++tok){
        //cout << "Beginning parse iter again" << endl;
        // << *(tok) << endl;
        if (*(tok) == "#") {
            break;
        }
        
        // cout << "CHECK PARENTHESES" << endl;
        
        //CHECK FOR PARENTHESES
        else if(*(tok) == "("){
            string internalCmd;
            tok++;
            while(*(tok) != ")"){
                internalCmd += *(tok);
                tok++;
            }
            cmdlist.push(recParse(internalCmd));
        }
        
        
        else if(*(tok) == "|"){
            tok++; 
            //| always comes in pairs so must ++ to skip iteration 
            
            Base* oor = new Or();
            connectorlist.push(oor);
        }
        else if(*(tok) == "&"){
            tok++;
            Base* aand = new And();
            connectorlist.push(aand);
        }
        else if(*(tok) == ";"){
            //do not need to skip, ; only has one iter
            
            Base* semicolon = new SemiColon();
            connectorlist.push(semicolon);
        }
        else{
            string toker = *(tok);
            while(toker.at(0) == ' '){ 
                // this is to remove extra whitespaces
                toker.erase(toker.begin());
                if(toker == ""){
                    break;
                }
            }
            //this is where we should create test and norm commands
            if(toker != ""){
                while(toker.at(toker.size()-1) == ' '){
                    toker.erase(toker.end()-1);
                    toker.resize(toker.size());
                }
            }
            
            stringstream ss;
            ss << toker;    //check
            
            string determString;
            ss >> determString;
            
            string tempHolder;
            
            if (determString == "[" || determString == "test") {
                //cout << "CREATING TESTCOMMAND" << endl;
                string finalString;
                ss >> finalString;
                //cout << "first finString check" << finalString << endl;
                if (finalString.size() == 2) {
                    ss >> tempHolder;
                    finalString += " " + tempHolder;
                    //cout << "second finString check: " << finalString << endl;
                }
                else{
                    string tempFinString = "-e " + finalString;
                    finalString = tempFinString;
                }
                //cout << "finalString Check: " << finalString << endl;
                Command* testcmd = new TestCommand(finalString);
                cmdlist.push(testcmd);
            }
    
            else{
                //cout << "CREATING NORMAL COMMAND" << endl;
                if(toker != ""){
                    normCommand* comnd = new normCommand(toker);
                    cmdlist.push(comnd);
                }
            }
        }
    }
}

void rShell::createExecuteList(){
    if (connectorlist.size()) {
        Base * lhs = cmdlist.front();
        cmdlist.pop();
        Base * rhs = cmdlist.front();
        cmdlist.pop();
        
        Base * conn = connectorlist.front();
        conn->setBase(lhs, rhs);
        connectorlist.pop();
        executeList.push(conn);
        
        while (!connectorlist.empty()) {
            if (!executeList.empty()) {
                lhs = executeList.front();
                executeList.pop();
            }
            
            rhs = cmdlist.front();
            cmdlist.pop();
            Base * conn = connectorlist.front();
            conn->setBase(lhs, rhs);
            connectorlist.pop();
            executeList.push(conn);
        }
        
    }
    
    if (cmdlist.size()) {
        executeList.push(cmdlist.front());
        cmdlist.pop();
    }
}

void rShell::Run() {
    while (!executeList.empty()) {
        //cout << "running..." << endl;
        executeList.front()->execute();
        //cout << "still running..." << endl;
        executeList.pop();
    }
}
        }
        else{
            string toker = *(tok);
            while(toker.at(0) == ' '){ 
                // this is to remove extra whitespaces
                toker.erase(toker.begin());
                if(toker == ""){
                    break;
                }
            }
            //this is where we should create test and norm commands
            if(toker != ""){
                while(toker.at(toker.size()-1) == ' '){
                    toker.erase(toker.end()-1);
                    toker.resize(toker.size());
                }
            }
            
            stringstream ss;
            ss << toker;    //check
            
            string determString;
            ss >> determString;
            
            string tempHolder;
            
            if (determString == "[" || determString == "test") {
                //cout << "CREATING TESTCOMMAND" << endl;
                string finalString;
                ss >> finalString;
                //cout << "first finString check" << finalString << endl;
                if (finalString.size() == 2) {
                    ss >> tempHolder;
                    finalString += " " + tempHolder;
                    //cout << "second finString check: " << finalString << endl;
                }
                else{
                    string tempFinString = "-e " + finalString;
                    finalString = tempFinString;
                }
                //cout << "finalString Check: " << finalString << endl;
                Command* testcmd = new TestCommand(finalString);
                cmdlist.push(testcmd);
            }
    
            else{
                //cout << "CREATING NORMAL COMMAND" << endl;
                if(toker != ""){
                    normCommand* comnd = new normCommand(toker);
                    cmdlist.push(comnd);
                }
            }
        }
    }
}

void rShell::createExecuteList(){
    if (connectorlist.size()) {
        Base * lhs = cmdlist.front();
        cmdlist.pop();
        Base * rhs = cmdlist.front();
        cmdlist.pop();
        
        Base * conn = connectorlist.front();
        conn->setBase(lhs, rhs);
        connectorlist.pop();
        executeList.push(conn);
        
        while (!connectorlist.empty()) {
            if (!executeList.empty()) {
                lhs = executeList.front();
                executeList.pop();
            }
            
            rhs = cmdlist.front();
            cmdlist.pop();
            Base * conn = connectorlist.front();
            conn->setBase(lhs, rhs);
            connectorlist.pop();
            executeList.push(conn);
        }
        
    }
    
    if (cmdlist.size()) {
        executeList.push(cmdlist.front());
        cmdlist.pop();
    }
}

void rShell::Run() {
    while (!executeList.empty()) {
        //cout << "running..." << endl;
        executeList.front()->execute();
        //cout << "still running..." << endl;
        executeList.pop();
    }
}
