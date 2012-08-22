/*
 * Term.cpp
 *
 *  Created on: 27.07.2012
 *      Author: solo
 */

#include "Term.h"

namespace lem {

Atom::Atom(const Atom& a) {
    type = a.type;

    void *p = (void*)&a.buf;
    if (type == CONST) {
        constructConst(*((Const*)p));
    } else if (type == VARIABLE) {
        constructVariable(*((Variable*)p));
    } else if (type == SYMBOL) {
        constructSymbol(*((CalculationSymbol*)p));
    } else {
        throw;
    }
}

Atom::Atom(const CalculationSymbol& v) {constructSymbol(v);}

Atom::Atom(const Const& c) {constructConst(c);}

Atom::Atom(const Variable& v) {constructVariable(v);}

void Atom::constructConst(const Const& c) {
    type = CONST;
    void* p = (void*)&buf;
    new(p) Const(c);
}

void Atom::constructSymbol(const CalculationSymbol& v) {
    type = SYMBOL;
    void* p = (void*)&buf;
    new(p) CalculationSymbol(v);
}

void Atom::constructVariable(const Variable& v) {
    type = VARIABLE;
    void* p = (void*)&buf;
    new(p) Variable(v);
}

Atom::~Atom() {
    if (type == CONST) {
        destructConst();
    } else if (type == VARIABLE) {
        destructVariable();
    } else if (type == SYMBOL) {
        destructSymbol();
    } else {
        throw;
    }
}

void Atom::destructConst() {}

void Atom::destructSymbol() {
    void* p = (void*)&buf;
    ((CalculationSymbol*)p)->~CalculationSymbol();
}

void Atom::destructVariable() {}

bool Term::isFunction() const {
    return (atoms.size() > 1);
}

bool Term::isSymbol() const {
    return ((atoms.size() == 1) && (atoms.begin()->isSymbol()));
}

bool Term::isVariable() const {
    return ((atoms.size() == 1) && (atoms.begin()->isVariable()));
}

bool Term::isConst() const {
    return ((atoms.size() == 1) && (atoms.begin()->isConst()));
}

void Term::erase() {
	atoms.clear();
}

}  /* namespace lem */
