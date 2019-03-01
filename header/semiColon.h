#ifndef SEMICOLON_H
#define SEMICOLON_H

#include "connector.h"

using namespace std;

class SemiColon : public Connector {
    public:
        SemiColon();
        bool isConnector();
        bool execute();
        void setBase(Base* a, Base* b);
};

#endif
