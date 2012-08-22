/*
 * Term.h
 *
 *  Created on: 27.07.2012
 *      Author: solo
 */

#ifndef TERM_H_
#define TERM_H_

#include "../lem.h"
#include "CalculationSymbol.h"
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
    Atom(const CalculationSymbol& v);
    Atom(const Const& c);
    Atom(const Variable& v);
    Atom(const Atom& a);

    ~Atom();

    bool isSymbol() const {return (type == SYMBOL);};
    bool isVariable() const {return (type == VARIABLE);};
    bool isConst() const {return (type == CONST);};

    const CalculationSymbol& getSymbol() const {return *((CalculationSymbol*)&buf);};
    const Const& getConst() const {return *((Const*)&buf);};
    const Variable& getVariable() const {return *((Variable*)&buf);};

private:
    enum {SYMBOL, VARIABLE, CONST} type;
    union {
        char variableMem[sizeof(Variable)];
        char constMem[sizeof(Const)];
        char valueMem[sizeof(CalculationSymbol)];
    } buf;

    void constructSymbol(const CalculationSymbol& v);
    void constructConst(const Const& v);
    void constructVariable(const Variable& v);

    void destructConst();
    void destructVariable();
    void destructSymbol();
};

class NestedAtom {
public:
    NestedAtom(const NestedAtom& a):left(a.left),right(a.right),atom(a.atom) {}
    NestedAtom(int l, const Atom& a, int r):left(l),right(r),atom(a) {}

    bool isSymbol() const {return atom.isSymbol();}
    bool isVariable() const {return atom.isVariable();}
    bool isConst() const {return atom.isConst();}

    const Atom& getAtom() const {return atom;}
    const CalculationSymbol& getSymbol() const {return atom.getSymbol();}
    const Const& getConst() const {return atom.getConst();}
    const Variable& getVariable() const {return atom.getVariable();}

    unsigned int getLeft() const {return left;}
    unsigned int getRight() const {return right;}
    void setleft(unsigned int l) {left = l;}
    void setRight(unsigned int r) {right = r;}
private:
    unsigned int left,right;
    Atom atom;
};

class Term {
public:
    Term() {};
    Term(const Term& t):atoms(t.atoms) {};
    ~Term() {};

    bool isFunction() const;
    bool isSymbol() const;
    bool isVariable() const;
    bool isConst() const;

    friend class TermUnifier;
private:
    typedef std::list<NestedAtom> atom_container;
    atom_container atoms;

    void erase();
};

inline bool operator==(const Variable& v1, const Variable& v2) {
    return ((v1.id == v2.id)&&(v1.step==v2.step));
}

inline bool operator<(const Variable& x, const Variable& y) {
    return (x.step < y.step)||((x.step==y.step) && (x.id < y.id));
}

} /* namespace lem */
#endif /* TERM_H_ */
