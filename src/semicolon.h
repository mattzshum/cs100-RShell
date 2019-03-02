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
    
    bool execute() {
        lhs->execute();
        rhs->execute();
        
        return true;
    }
    
    void setBase(Base* a, Base* b){
        lhs = a;
        rhs = b;
    }
};

#endif
