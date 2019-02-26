#ifndef _BASE_H_
#define _BASE_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>

using namespace std;

class Base {
    public:
        Base* lhs;
        Base* rhs;
        void set(Base *lhs, Base *rhs) {
            this->lhs = lhs;
            this->rhs = rhs;
        }
        virtual int execute() = 0;
};

#endif