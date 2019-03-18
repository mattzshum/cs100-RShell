#ifndef OR_H
#define OR_H

#include "connector.h"

using namespace std;

class Or : public Connector{
  public:
    Or() { }
    
    bool isConnector(){
      return true;
    }
    
    string getCommand() { return "";}
    
    bool execute(int in , int out){
        if( !( lhs->execute(0,0) ) ){
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
