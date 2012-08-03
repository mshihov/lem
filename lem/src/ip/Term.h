/*
 * Term.h
 *
 *  Created on: 27.07.2012
 *      Author: solo
 */

#ifndef TERM_H_
#define TERM_H_

#include "Value.h"
#include<new>
#include<list>

namespace lem {

class Const {
    unsigned int id;
public:
    Const(unsigned int id_):id(id_) {};
    Const(const Const& c):id(c.id) {};
    unsigned int getId() const {return id;};
};


class Variable {
public:
    Variable(unsigned int id_, unsigned int step_):id(id_),step(step_) {};
    Variable(const Variable& v):id(v.id),step(v.step) {};

    unsigned int getId() const {return id;};
    unsigned int getStep() const {return step;};
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
    int left,right;
    Atom atom;
public:
    NestedAtom(int l, const Atom& a, int r);

    bool isValue() const;
    bool isVariable() const;
    bool isConst() const;
};

class Term {
public:
    Term();

    //possible term states
    bool isEval() const;
    bool isFunctor() const;
    bool isValue() const;
    bool isVariable() const;
    bool isConst() const;

    //TODO static SHAREDPTR<TermSubstPair> unify(const Term& t1, const Term& t2);
    //static TermSubstPair unify(const TermSubstPair& t1, const TermSubstPair& t2);
private:
    std::list<NestedAtom> alist;
};

}
#endif /* TERM_H_ */
