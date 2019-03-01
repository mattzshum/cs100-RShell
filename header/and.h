#ifndef AND_H
#define AND_H

#include "connector.h"

using namespace std;

class And : public Connector{
    public:
        And();
        bool isConnector();
        bool execute();
        void setBase(Base* a, Base* b);
};

#endif
