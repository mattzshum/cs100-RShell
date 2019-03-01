#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "base.h"

using namespace std;

/*
Connectors act as the operands in lab3 and 4. They will purely execute what is passed into them and return a boolean value of whether or not it passed.
The boolean it returns will be determined by the command it is assigned.
*/

class Connector : public Base{
    protected:
        Base* lhs;
        Base* rhs;
    
    public:
        Connector();
        virtual bool isConnector() = 0;
        virtual void setBase(Base* a, Base* b) = 0;
        virtual bool execute() = 0;
};

#endif
