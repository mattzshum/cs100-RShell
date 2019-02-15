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

#include "Or.h"

Or::Or(){
   lhs = 0;
   rhs = 0;
}

Or::Or(Base* left, Base* right){
   this->lhs = left;
   this->rhs = right;
}

//chcek status, if it returns a invalid value do nto run next command
int Or::execute(){
   int status = 0;
   status = first->execute();
   if(status!=0){
      status = second->execute();
      return status;
   }
   return status;
}
