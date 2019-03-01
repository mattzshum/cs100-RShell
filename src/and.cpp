#include <iostream>

using namespace std;

#include "../header/and.h"

And::And() {};

bool And::isConnector() {
    return true;
}

bool And::execute() {
    if (lhs->execute()) {
        return rhs->execute();
    }
    return false;
}

void And::setBase(Base* a, Base* b) {
    lhs = a;
    rhs = b;
}
