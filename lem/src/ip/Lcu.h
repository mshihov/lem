/*
 * Lcu.h --- lesser common unifier class
 *
 *  Created on: 17.08.2012
 *      Author: solo
 */

#ifndef LCU_H_
#define LCU_H_

#include <list>
#include "Term.h"
#include "../utils/Ptr.h"

namespace lem {

class VariableValue {
public:
    VariableValue(const Variable& v):variable(v) {}
    VariableValue(const Variable& v, const Variable& vt):term(vt),variable(v) {}
    VariableValue(const Variable& v, const Const& ct):term(ct),variable(v) {}
    VariableValue(const Variable& v, const CalculationSymbol& st):term(st),variable(v) {}
    VariableValue(const Variable& v, const Term& t):term(t),variable(v) {}

    const Term &getTerm() const { return term; }
    const Variable &getVariable() const { return variable; }

    friend class TermUnifier;
private:
    Term term;
    Variable variable;
};

class VariableEvalue { //TODO constant mapping in calculation process
    const Term &getTerm() const { return term; }
    const Variable &getVariable() const { return variable; }
private:
    Term term;
    Variable variable;
};

class Lcu {
public:
    typedef VariableValue value_type;
    typedef Ptr<value_type> value_ptr_type;
    typedef std::list<value_ptr_type> value_container_type;
    typedef std::list<VariableEvalue> evalue_container_type;

    Lcu():inconsistent(false) {}
    Lcu(const Lcu& l):inconsistent(l.inconsistent),vals(l.vals),evals(l.evals) {}
    Lcu(const value_container_type& unifiers) { appendValues(unifiers); }
    ~Lcu() {}

    bool isEmpty() const { return (!isInconsistent() && vals.size() == 0 && evals.size() == 0); }
    bool isInconsistent() const { return inconsistent; }
    bool appendValues(const value_container_type& unifiers);
    bool doConsistent();

    Lcu& operator+= (const Lcu& x);

    friend class TermUnifier;
private:
	bool inconsistent;
    value_container_type vals;
    evalue_container_type evals;

    void setInconsistent();
    bool appendValue(const value_ptr_type& value);
    bool orderedInstall(value_container_type& valStack);
    bool installNewItems(value_container_type& valStack);
};

} /* namespace lem */
#endif /* LCU_H_ */
