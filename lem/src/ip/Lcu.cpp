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
        if (!appendValue(*it))
            return false;
    }
    return true;
}

bool Lcu::appendValue(const value_ptr_type& val) {
    value_container_type valStack;

    valStack.push_back(val);
    return installNewItems(valStack);
}

bool Lcu::installNewItems(value_container_type& valStack) {
    while (valStack.size() != 0) {
        if (!orderedInstall(valStack)) {
            return false;
        }
    }
    return true;
}

bool Lcu::orderedInstall(value_container_type& valStack) {
    value_ptr_type val = *(valStack.begin());
    valStack.pop_front();

    typename value_container_type::iterator it;

    for (it=vals.begin(); it != vals.end(); ++it) {
        if ((*it)->getVariable() >= val->getVariable()) {
            if ((*it)->getVariable() == val->getVariable()) {
                TermUnifier unifier((*it)->getTerm(), val->getTerm());

                if (unifier.isBad()) {
                    setInconsistent();
                    return false;
                }
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
    //TODO check conflicts as {f(y)/x, g(x)/y}
    return true;
}

Lcu& Lcu::operator+= (const Lcu& x) {
    if (x.isInconsistent()) {
        setInconsistent();
        return *this;
    }

    value_container_type valStack;
    typename value_container_type::const_iterator   itX = x.vals.begin(),   itXEnd = x.vals.end();
    typename value_container_type::iterator         it = vals.begin(),      itEnd = vals.end();

    while (itX != itXEnd) {
        if (it == itEnd) {
            vals.insert(it, *itX);
            ++itX;
        } else if ((*it)->getVariable() >= (*itX)->getVariable()) {
            if ((*it)->getVariable() == (*itX)->getVariable()) {
                TermUnifier unifier((*it)->getTerm(), (*itX)->getTerm());

                if (unifier.isBad()) {
                    setInconsistent();
                    return *this;
                }
                if (!unifier.isEmpty()) {
                    *it = value_ptr_type(new value_type((*itX)->getVariable(), unifier.getTerm()));
                    const value_container_type& newItems = unifier.getLcuItems();
                    valStack.insert(valStack.end(), newItems.begin(), newItems.end());
                }
                ++it;
            } else {
                vals.insert(it, *itX);
            }
            ++itX;
        } else {
            ++it;
        }
    }
    installNewItems(valStack);
    return *this;
}


} /* namespace lem */
