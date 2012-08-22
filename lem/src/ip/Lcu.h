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

namespace lem {

class VariableValue {
    const Term &getTerm() const { return term; }
    const Variable &getVariable() const { return variable; }
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
    Lcu():inconsistent(false) {}
    Lcu(const Lcu& l):inconsistent(l.inconsistent),vals(l.vals),evals(l.evals) {}
    ~Lcu() {}

    bool isEmpty() const { return (!isInconsistent() && vals.size() == 0 && evals.size() == 0); }
    bool isInconsistent() const { return inconsistent; }
    Lcu& operator+= (const Lcu& x);

    friend class TermUnifier;
private:
    bool inconsistent;
    std::list<VariableValue> vals;
    std::list<VariableEvalue> evals;
};

} /* namespace lem */
#endif /* LCU_H_ */
