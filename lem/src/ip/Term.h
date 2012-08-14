/*
 * Term.h
 *
 *  Created on: 27.07.2012
 *      Author: solo
 */

#ifndef TERM_H_
#define TERM_H_

#include "../lem.h"
#include "Value.h"
#include<new>
#include<list>

namespace lem {

class Const {
public:
    Const(unsigned int id_):id(id_) {};
    Const(const Const& c):id(c.id) {};
    unsigned int getId() const {return id;};
    friend bool operator==(const Const& c1, const Const& c2) {return c1.id == c2.id;};
    friend bool operator!=(const Const& c1, const Const& c2) {return !(c1==c2);};
private:
    unsigned int id;
};

class Variable {
public:
    Variable(unsigned int id_, unsigned int step_):id(id_),step(step_) {};
    Variable(const Variable& v):id(v.id),step(v.step) {};

    unsigned int getId() const {return id;};
    unsigned int getStep() const {return step;};
    friend bool operator==(const Variable& v1, const Variable& v2);
    friend bool operator<(const Variable& v1, const Variable& v2);

private:
    unsigned int id;
    unsigned int step; //of logical computation
};

class Atom {
public:
    Atom(const Value& v);
    Atom(const Const& c);
    Atom(const Variable& v);
    Atom(const Atom& a);

    ~Atom();

    bool isValue() const {return (type == VALUE);};
    bool isVariable() const {return (type == VARIABLE);};
    bool isConst() const {return (type == CONST);};

    const Value& getValue() {return *((Value*)&buf);};
    const Const& getConst() {return *((Const*)&buf);};
    const Variable& getVariable() {return *((Variable*)&buf);};

private:
    enum {VALUE, VARIABLE, CONST} type;
    union {
        char variableMem[sizeof(Variable)];
        char constMem[sizeof(Const)];
        char valueMem[sizeof(Value)];
    } buf;

    void constructValue(const Value& v);
    void constructConst(const Const& v);
    void constructVariable(const Variable& v);

    void destructConst();
    void destructVariable();
    void destructValue();
};

class NestedAtom {
public:
    NestedAtom(int l, const Atom& a, int r);

    bool isValue() const {return atom.isValue();};
    bool isVariable() const {return atom.isVariable();};
    bool isConst() const {return atom.isConst();};

    const Value& getValue() {return atom.getValue();};
    const Const& getConst() {return atom.getConst();};
    const Variable& getVariable() {return atom.getVariable();};

    unsigned int getLeft() const {return left;};
    unsigned int getRight() const {return right;};
    void setleft(unsigned int l) {left = l;}
    void setRight(unsigned int r) {right = r;}
private:
    unsigned int left,right;
    Atom atom;
};

class Term {
public:
    Term();

    //TODO static SHAREDPTR<TermSubstPair> unify(const Term& t1, const Term& t2);
    //static TermSubstPair unify(const TermSubstPair& t1, const TermSubstPair& t2);
private:
    std::list<NestedAtom> alist;
};

inline bool operator==(const Variable& v1, const Variable& v2) {
    return ((v1.id == v2.id)&&(v1.step==v2.step));
}

inline bool operator<(const Variable& x, const Variable& y) {
    return (x.step < y.step)||((x.step==y.step) && (x.id < y.id));
}

} /* namespace lem */
#endif /* TERM_H_ */
