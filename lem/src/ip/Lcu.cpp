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

bool Lcu::appendValues(const value_container_type& newVals) {
    typename value_container_type::const_iterator it = newVals.begin();

    for (it = newVals.begin(); it != newVals.end(); ++it) {
        if (!appendValue(*it)) {
            setInconsistent();
            return false;
        }
    }
    return true;
}

bool Lcu::appendValue(const value_ptr_type& val) {
    value_container_type valStack;

    valStack.push_back(val);
    while (valStack.size() == 0) {
        value_ptr_type vp = *(valStack.begin());
        valStack.pop_front();

        orderedInstall(vp, valStack);
    }
    return true;
}

bool Lcu::orderedInstall(const value_ptr_type& val, value_container_type& valStack) {
    typename value_container_type::iterator it;

    for (it=vals.begin(); it != vals.end(); ++it) {
        if ((*it)->getVariable() >= val->getVariable()) {
            if ((*it)->getVariable() == val->getVariable()) {
                TermUnifier unifier((*it)->getTerm(), val->getTerm());

                if (unifier.isBad())
                    return false;

                if (!unifier.isEmpty()) {
                    *it = value_ptr_type(new value_type(val->getVariable(), unifier.getTerm()));
                    const value_container_type& newItems = unifier.getLcuItems();
                    valStack.insert(valStack.end(), newItems.begin(), newItems.end());
                }
            } else {
                vals.insert(it, val);
            }
            break;
        }
    }
    if (it == vals.end()) {
        vals.insert(it, val);
    }
    return true;
}

bool Lcu::doConsistent() {
    return true;
}


} /* namespace lem */
