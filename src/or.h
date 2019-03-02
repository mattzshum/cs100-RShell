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
    
    bool execute(){
        if( !( lhs->execute() ) ){
            return rhs->execute();
        }
        return false;
    }
    
    void setBase(Base* a, Base* b){
        lhs = a;
        rhs = b;
    }
};

#endif