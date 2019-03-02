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
    
    bool execute() {#ifndef AND_H
#define AND_H

#include "connector.h"

using namespace std;

class And : public Connector{
  public:
    And() { }
    
    bool isConnector(){
      return true;
    }
    
    bool execute() {
        if(lhs->execute()){
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
        if(lhs->execute()){
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
