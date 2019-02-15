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
   first = 0;
   second = 0;
}

And::And(Base* first, Base* second){
   this->first = first;
   this->second = second;
}

And::And(Base* first, Command* second) {
   this->first = first;
   this->second = second;
}

int And::execute(){
   int status = 0;
   status = first->execute();
   if(status != 0){
      return -1;
   } else {
      status = second->execute();
      if(status != 0){
         return -1;
      }
   }
   return status;
}
