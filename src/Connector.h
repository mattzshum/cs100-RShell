#ifndef _CONNECTOR_H_
#define _CONNECTOR_H_

#include "Base.h"

using namespace std;

class Connector : public Base {
    protected:
        Base* lhs;
        Base* rhs;
    public:
        Connector();
        Connector(Base* left, Base* right);
        virtual int execute();
};

#endif