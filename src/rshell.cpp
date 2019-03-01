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
#include "semiColon.h"
#include "and.h"
#include "connector.h"
#include "command.h"

using namespace std;
using namespace boost;

void rShell::display(){
    cout << "$ ";
}

void rShell::parse(string cmdLine) {
    typedef tokenizer<char_separator<char> > tokenizer;
    char_separator<char> split("", "&;|#", drop_empty_tokens);
    tokenizer tokens(cmdLine, split);
    for(tokenizer::iterator tok = tokens.begin(); tok != tokens.end(); ++tok){
        if (*(tok) == "#") {
            break;
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
            if(toker != ""){
                while(toker.at(toker.size()-1) == ' '){
                    toker.erase(toker.end()-1);
                    toker.resize(toker.size());
                }
            }
            if(toker != ""){
                Command* comnd = new Command(toker);
                cmdlist.push(comnd);
            }
        }
    }
}

void rShell::createExecuteList() {
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
        executeList.front()->execute();
        executeList.pop();
    }
}
