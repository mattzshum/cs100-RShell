#ifndef AND_H
#define AND_H
#include "Connector.h"
#include "Command.h"
class And: public Connector {
   //declare pointers and constructors
   private:
      Base* first;
      Base* second;
   public:
      And();
      And(Base* first, Base* second);
      And(Base* first, Command* second);
      int execute();
};
#endif
