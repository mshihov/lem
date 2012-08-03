//============================================================================
// Name        : lem.cpp
// Author      : M.M.Shihov
// Version     : 1.0
// Copyright   : free
// Description : Logical EMulator
//============================================================================

#include <iostream>
#include "ip/Term.h"

using namespace lem;

void foo() {
    Atom atom(Const(3));
    foo();
    foo();
}

int main() {
    std::cout << "sizeof(Value)" << sizeof(Value) << "\n";
    std::cout << "sizeof(Const)" << sizeof(Const) << "\n";
    std::cout << "sizeof(Variable)" << sizeof(Variable) << "\n";
    std::cout << "sizeof(Atom)" << sizeof(Atom) << "\n";
    std::cin.get();
	return 0;
}


