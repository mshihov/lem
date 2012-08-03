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
    } else if (type == VALUE) {
        constructValue(*((Value*)p));
    } else {
        throw;
    }
}

Atom::Atom(const Value& v) {constructValue(v);}

Atom::Atom(const Const& c) {constructConst(c);}

Atom::Atom(const Variable& v) {constructVariable(v);}

void Atom::constructConst(const Const& c) {
    type = CONST;
    void* p = (void*)&buf;
    new(p) Const(c);
}

void Atom::constructValue(const Value& v) {
    type = VALUE;
    void* p = (void*)&buf;
    new(p) Value(v);
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
    } else if (type == VALUE) {
        destructValue();
    } else {
        throw;
    }
}

void Atom::destructConst() {}

void Atom::destructValue() {
    void* p = (void*)&buf;
    ((Value*)p)->~Value();
}

void Atom::destructVariable() {}

Term::Term() {
    // TODO Auto-generated constructor stub

}


}
