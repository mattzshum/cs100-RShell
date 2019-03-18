#ifndef AND_H
#define AND_H

#include "connector.h"

using namespace std;

class And : public Connector{
  public:
    And() { }
    
    bool isConnector(){
      return true;
    }
    
    string getCommand() { return "";}
    
    bool execute(int in, int out) {
        if(lhs->execute(0,0)){
            return rhs->execute(0,0);
        }
        return false;
    }
    
    void setBase(Base* a, Base* b){
        lhs = a;
        rhs = b;
    }
};

#endif
