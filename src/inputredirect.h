#ifndef INPUTREDIRECT_H
#define INPUTREDIRECT_H

#include "connector.h"
#include "base.h"

using namespace std;

class InputRedirect : public Connector{
  public:
    InputRedirect() : Connector() {};
    
    bool isConnector() { return true; }
    void setBase(Base* a, Base* b){
        lhs = a;
        rhs = b;
    }
    
    string getCommand() { return "";}
    
    bool execute(int in, int out){
        string inputFile = rhs->getCommand();
        in = open(inputFile.c_str(), O_RDONLY);
        
        lhs->execute(in, 1);
    }
};

#endif
