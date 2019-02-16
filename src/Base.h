#ifndef _BASE_H_
#define _BASE_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>

using namespace std;

class Base {
    public:
        virtual int execute() = 0;
};

#endif