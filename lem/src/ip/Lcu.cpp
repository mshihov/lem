/*
 * Lcu.cpp
 *
 *  Created on: 17.08.2012
 *      Author: solo
 */

#include "Lcu.h"
#include "TermUnifier.h"
#include<iterator>

namespace lem {

void Lcu::setInconsistent() {
	inconsistent = true;
	vals.clear();
	evals.clear();
}

bool Lcu::appendValues(const value_container& newVals) {
    typename value_container::const_iterator it = newVals.begin();

    for (it = newVals.begin(); it != newVals.end(); ++it) {
        if (!appendValue(*it)) { setInconsistent(); return false; }

    }
    return true;
}

bool Lcu::appendValue(const value_type& v) {
    value_type vtmp = v;
    typename value_container::iterator it;
    value_container stack;

    while (true) {
        for (it=vals.begin(); it != vals.end(); ++it) {
            if (it->getVariable() >= v.getVariable()) {
                if (it->getVariable() == v.getVariable()) {
                    TermUnifier u(it->getTerm(), v.getTerm());

                    if (u.isUnificationFailed()) { return false; }
                    if (!u.termsIsEquals()) {
                        value_type t(v.getVariable(), u.getTerm());
                        *it = t;

                        const value_container& unifiers = u.getUnifiers();
                        stack.insert(stack.end(), unifiers.begin(), unifiers.end());
                        break;
                    }
                } else {
                    vals.insert(it, v);
                    break;
                }
            }
        }
        if (it == vals.end()) {
            vals.insert(it, v);
        }

        if (stack.size() == 0) { return true; }
        vtmp = *(stack.begin());
        stack.pop_front();
    }
    return false;
}

bool Lcu::doConsistent() {
    return true;
}


} /* namespace lem */
