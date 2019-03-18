#ifndef SEMICOLON_H
#define SEMICOLON_H

#include "connector.h"

using namespace std;

class SemiColon : public Connector{
  public:
    SemiColon() { }
    
    bool isConnector(){
      return true;
    }
    
    bool execute(int in, int out) {
        lhs->execute(0,0);
        rhs->execute(0,0);
        
        return true;
    }
    
    string getCommand() { return "";}
    
    void setBase(Base* a, Base* b){
        lhs = a;
        rhs = b;
    }
};

#endif
