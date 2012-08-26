/*
 * Lcu.cpp
 *
 *  Created on: 17.08.2012
 *      Author: solo
 */

#include "Lcu.h"
#include "TermUnifier.h"

namespace lem {

void Lcu::setInconsistent() {
	inconsistent = true;
	vals.clear();
	evals.clear();
}

bool Lcu::appendValues(const value_container& newValues) {
    typename value_container::iterator itVals;
    typename value_container::const_iterator itUnifiers = newValues.begin();
    value_container stack;

    while(true) {
        if (itUnifiers == newValues.end()) { break; }
        for (itVals = vals.begin(); itVals != vals.end(); ++itVals) {
            if (itVals->getVariable() == itUnifiers->getVariable()) {
                TermUnifier unifier(itVals->getTerm(), itUnifiers->getTerm());
            }
        }
    }
    return false;
}

bool Lcu::doConsistent() {
    return true;
}


} /* namespace lem */
