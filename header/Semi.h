#ifndef SEMI_H
#define SEMI_H
#include "Connector.h"


class Semi: public Connector {
   //declare private pointers and constructors
   private:
      Base* lhs;
      Base* rhs;
   public:
      Semi();
      Semi(Base* left, Base* right);  
      int execute();
};

#endif