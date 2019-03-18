#ifndef OUTPUTREDIRECT_H
#define OUPUTREDIRECT_H

#include "connector.h"

class OutputRedirect : public Connector{
  public:
    OutputRedirect() : Connector() {};
    
    bool isConnector() { return true; }
    void setBase(Base* a, Base* b){
        lhs = a;
        rhs = b;
    }
    
    string getCommand() { return "";}
    
    bool execute(int in, int out){
        string outputFile = rhs->getCommand();
        out = open(outputFile.c_str(), O_WRONLY| O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
        
        lhs->execute(0, out);
    }
};

#endif
