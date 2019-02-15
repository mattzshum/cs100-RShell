#ifndef OR_H
#define OR_H
#include "Connector.h"
#include "Command.h"

class Or: public Connector{
   //declare constructors and member pointers
   private:
      Base* lhs;
      Base* rhs;
   public:
      Or();
      Or(Base* left, Base* right);
      int execute();
};
#endif
