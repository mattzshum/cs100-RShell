#include "../header/semiColon.h"

using namespace std;

SemiColon::SemiColon() {};
    
bool SemiColon::isConnector(){
    return true;
}
    
bool SemiColon::execute() {
    lhs->execute();
    rhs->execute();
    return true;
}
    
void SemiColon::setBase(Base* a, Base* b){
    lhs = a;
    rhs = b;
}
