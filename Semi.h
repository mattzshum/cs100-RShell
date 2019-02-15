#ifndef SEMI_H
#define SEMI_H
#include "Connector.h"
#include "Command.h"

class Semi: public Connector {
   //declare private pointers and constructors
   private:
      Base* first;
      Base* second;
   public:
      Semi();
      Semi(Base* first, Base* second);
      Semi(Base* first, Command* second);
      int execute();
}
#endif

