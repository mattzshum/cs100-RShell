#ifndef OR_H
#define OR_H
#include "Connector.h"
#include "Command.h"

class Or: public Connector{
   //declare constructors and member pointers
   private:
      Base* first;
      Base* second;
   public:
      Or();
      Or(Base* first, Connector* second);
      Or(Base* first, Base* second);
      int execute();
};
#endif
