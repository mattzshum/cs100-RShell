#include "or.h"

using namespace std;

Or::Or() {};
    
bool Or::isConnector() {
    return true;
}
    
bool Or::execute() {
    if (!(lhs->execute())) {
        return rhs->execute();
    }
    return false;
}
    
void Or::setBase(Base* a, Base* b) {
    lhs = a;
    rhs = b;
}
