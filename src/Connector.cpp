#include "Connector.h"

Connector::Connector() 
{}

Connector::Connector(Base* left, Base* right, string c) {
    lhs = left;
    rhs = right;
    cnctr = c;
}

int Connector::execute() {
    int status = -1;
    if (cnctr == "&&") {
        if (lhs->execute()) {
            rhs->execute();
        }
    }
    else if (cnctr == "||") {
        if (!lhs->execute()) {
            rhs->execute();
        }
    }
    else {
        lhs->execute();
        rhs->execute();
    }
    return status;
}