//============================================================================
// Name        : lem.cpp
// Author      : M.M.Shihov
// Version     : 1.0
// Copyright   : free
// Description : Logical EMulator
//============================================================================

#include <iostream>
#include "ip/Term.h"


void foo() {
    lem::Atom a(lem::Variable(0,0));
    const lem::Variable& v = a.getVariable();
    v == v;
}

int main() {
    foo();
	return 0;
}


