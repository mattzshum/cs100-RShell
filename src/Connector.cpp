#include "Connector.h"

Connector::Connector() {
    lhs = 0;
    rhs = 0;
}

Connector::Connector(Base* left, Base* right) {
    lhs = left;
    rhs = right;
}

int Connector::execute() {
    int status = 0;
    status = lhs->execute();
    if (status != 0) {
        return -1;
    }  
    else {
        status = rhs->execute();
        if (status != 0) {
            return -1;
        }
    }
    return status;
}