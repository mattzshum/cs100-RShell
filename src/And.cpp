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

#include "Connector.h"


And::And(){
   rhs = 0;
   lhs = 0;
}

And::And(Base* left, Base* right){
   this->rhs = right;
   this->lhs = left;
}

int And::execute(){
   int status = 0;
   status = lhs->execute();
   if(status != 0){
      return -1;
   } else {
      status = rhs->execute();
      if(status != 0){
         return -1;
      }
   }
   return status;
}
