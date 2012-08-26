//============================================================================
// Name        : lem.cpp
// Author      : M.M.Shihov
// Version     : 1.0
// Copyright   : free
// Description : Logical EMulator
//============================================================================

#include <iostream>
#include "utils/Ptr.h"

class C {
public:
    C() {std::cout << "C constructed\n";}
    ~C() {std::cout << "C destroyed\n";}
};



lem::Ptr<C> foo() {
    std::cout << "foo()";
    lem::Ptr<C> p(new C());
    return p;
}

void bar() {
    std::cout << "bar(): call foo()";
    lem::Ptr<C> p = foo();
    std::cout << "exit bar()";
}

int main() {
    bar();
	return 0;
}


