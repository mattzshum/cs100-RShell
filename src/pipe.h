#ifndef PIPE_H
#define PIPE_H

#include "connector.h"

class Pipe : public Connector{
  public:
    Pipe() : Connector() {};
    
    bool isConnector() { return true; }
    void setBase(Base* a, Base* b){
        lhs = a;
        rhs = b;
    }
    
    string getCommand() { return "";}
    
    bool execute(int in, int out){
        /*string outputFile = rhs->getCommand();
        string inputFile = lhs->getCommand();
        out = open(outputFile.c_str(), O_WRONLY| O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
        in = open(inputFile.c_str(), O_RDONLY);//O_WRONLY| O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
        
        if(!lhs->execute(in, out)){
            return false;
        }
        if(!rhs->execute(in, out)){
            return false;
        }
        return true;*/
    }
};

#endif
