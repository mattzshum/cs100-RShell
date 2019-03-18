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
#include "outputredirect.h"
#include "inputredirect.h"
#include "doubleoutput.h"
#include "pipe.h"

using namespace std;
using namespace boost;

void rShell::display(){
    cout << "$ ";
}

Base* rShell::recParse(string internalCommand) { //TODO
    typedef tokenizer<char_separator<char> > tokenizer;
    char_separator<char> split("", "&;|#()<>", drop_empty_tokens);
    tokenizer tokens(internalCommand, split);
    tokenizer::iterator fol = tokens.begin();
    for(tokenizer::iterator tok = tokens.begin(); tok != tokens.end(); ++tok){
        if(*(tok) == "#"){
            break;
        }
        else if(*(tok) == "("){
            string internalCmd;
            tok++;
            fol++;
            while(*(tok) != ")"){
                internalCmd += *(tok);
                tok++;
                fol++;
            }
            cmdlist.push(recParse(internalCmd));
        }
        else if(*(tok) == "|"){
            fol++;
            fol++; // Play around with. Creates OOR despite incrementing here
            if((*fol) == "|"){
                //cout << "has created OOR" << endl;
                tok++;
                Base* oor = new Or();
                connectorListRecursive.push(oor);
            }
            else{
                //cout << "has created PIPE" << endl;
                Base* pipe = new Pipe();
                connectorListRecursive.push(pipe);
                //tok++;
            }
        }
        else if(*(tok) == "&"){
            tok++;
            fol++;
            Base* aand = new And();
            connectorListRecursive.push(aand);
        }
        else if(*(tok) == ";"){
            //do not need to skip, ; only has one iter
            
            Base* semicolon = new SemiColon();
            connectorListRecursive.push(semicolon);
        }
        else if((*tok) == "<"){
            Base* inputredirect = new InputRedirect();
            connectorListRecursive.push(inputredirect);
        }
        else if((*tok) == ">"){
            fol++;
            fol++;
            if((*fol) == ">"){
                Base* doubleoutput = new DoubleOutput();
                connectorListRecursive.push(doubleoutput);
                tok++;
            }
            else{
                Base* outputredirect = new OutputRedirect();
                connectorListRecursive.push(outputredirect);
            }
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
    if(connectorListRecursive.empty()){
        Base* ret = cmdListRecursive.front();
        return ret;
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
    char_separator<char> split("", "&;|#()<>",drop_empty_tokens);
    tokenizer tokens(cmdLine, split);
    tokenizer::iterator fol = tokens.begin(); // this is a token we would use to follow tok & check for double recurrences
    for(tokenizer::iterator tok = tokens.begin(); tok != tokens.end(); ++tok){
        if (*(tok) == "#") {
            break;
        }
        else if(*(tok) == "("){
            string internalCmd;
            tok++;
            fol++;
            while(*(tok) != ")"){
                internalCmd += *(tok);
                tok++;
                fol++;
            }
            cmdlist.push(recParse(internalCmd));
        }
        
        else if(*(tok) == "|"){
            fol++;
            fol++; // Play around with. Creates OOR despite incrementing here
            if((*fol) == "|"){
                cout << "has created OOR" << endl;
                tok++;
                Base* oor = new Or();
                connectorlist.push(oor);
            }
            else{
                cout << "has created PIPE" << endl;
                Base* pipe = new Pipe();
                connectorlist.push(pipe);
                //tok++;
            }
        }
        else if(*(tok) == "&"){
            tok++;
            fol++;
            Base* aand = new And();
            connectorlist.push(aand);
        }
        else if(*(tok) == ";"){
            Base* semicolon = new SemiColon();
            connectorlist.push(semicolon);
        }
        else if((*tok) == "<"){
            Base* inputredirect = new InputRedirect();
            connectorlist.push(inputredirect);
        }
        else if((*tok) == ">"){
            fol++;
            fol++;
            if((*fol) == ">"){
                Base* doubleoutput = new DoubleOutput();
                connectorlist.push(doubleoutput);
                tok++;
            }
            else{
                Base* outputredirect = new OutputRedirect();
                connectorlist.push(outputredirect);
            }
        }
        else{
            string toker = *(tok);
            while(toker.at(0) == ' '){ 
                toker.erase(toker.begin());
                if(toker == ""){
                    break;
                }
            }
            if(toker != ""){
                while(toker.at(toker.size()-1) == ' '){
                    toker.erase(toker.end()-1);
                    toker.resize(toker.size());
                }
            }
            
            stringstream ss;
            ss << toker;
            
            string determString;
            ss >> determString;
            
            string tempHolder;
            
            if (determString == "[" || determString == "test") {
                string finalString;
                ss >> finalString;
                if (finalString.size() == 2) {
                    ss >> tempHolder;
                    finalString += " " + tempHolder;
                }
                else{
                    string tempFinString = "-e " + finalString;
                    finalString = tempFinString;
                }
                Command* testcmd = new TestCommand(finalString);
                cmdlist.push(testcmd);
            }
    
            else{
                if(toker != ""){
                    normCommand* comnd = new normCommand(toker);
                    cmdlist.push(comnd);
                }
            }
            //cout << "TOKENIZER: " << (*tok) << endl;
            //cout << "FOLLOWER: " << (*tok) << endl;
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
        executeList.front()->execute(0,0);
        executeList.pop();
    }
}
