#ifndef _CONNECTOR_H_
#define _CONNECTOR_H_

#include "Base.h"

using namespace std;

class Connector : public Base {
    protected:
        Base* lhs;
        Base* rhs;
        string cnctr;
    public:
        Connector();
        Connector(Base* left, Base* right, string cnctr);
        virtual int execute();
};

#endif