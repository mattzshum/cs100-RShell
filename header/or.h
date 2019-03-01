#ifndef OR_H
#define OR_H

#include "connector.h"

using namespace std;

class Or : public Connector{
    public:
        Or();
        bool isConnector();
        bool execute();
        void setBase(Base* a, Base* b);
};

#endif
