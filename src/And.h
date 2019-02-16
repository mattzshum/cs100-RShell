#ifndef AND_H
#define AND_H
#include "Connector.h"

class And: public Connector {
   //declare pointers and constructors
   private:
      Base* lhs;
      Base* rhs;
   public:
      And();
      And(Base* left, Base* right);
      int execute();
};
#endif
