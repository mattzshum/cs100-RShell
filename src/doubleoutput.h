#ifndef DOUBLEOUTPUT_H
#define DOUBLEOUTPUT_H

#include "connector.h"

class DoubleOutput : public Connector{
  public:
    DoubleOutput() : Connector() {};
    
    bool isConnector() { return true; }
    void setBase(Base* a, Base* b){
        lhs = a;
        rhs = b;
    }
    
    string getCommand() { return "";}
    
    bool execute(int in, int out){
        string outputFile = rhs->getCommand();
        out = open(outputFile.c_str(), O_WRONLY| O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
        
        lhs->execute(0, out);
    }
};

#endif
