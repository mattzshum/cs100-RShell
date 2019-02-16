#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
#include <stdio.h>
#include <unistd.h>

using namespace std;

#include "Semi.h"

Semi::Semi(){
   lhs = 0;
   rhs = 0;
}

Semi::Semi(Base* left, Base* right){
   this->lhs = left;
   this->rhs = right;
}

int Semi::execute(){
   int status = 0;
   status = rhs->execute();
   status = lhs->execute();
   return status;
}
