/*
 * TermUnifier.cpp
 *
 *  Created on: 18.08.2012
 *      Author: solo
 */

#include "TermUnifier.h"
#include <algorithm>

namespace lem {

void TermUnifier::doUnification(const Term& x, const Term& y) {
    typename atom_container::const_iterator ix = x.atoms.begin();
    typename atom_container::const_iterator ex = x.atoms.end();
    typename atom_container::const_iterator iy = y.atoms.begin();
    typename atom_container::const_iterator ey = y.atoms.end();

    while(true) {
        if ((ix == ex) && (iy == ey)) { break; }
        if ((ix == ex) || (iy == ey)) { failUnification(); break; }

        if (ix->getLeft() > iy->getLeft()) {
            std::swap(ix,iy);
            std::swap(ex,ey);
        }

        if (ix->getLeft() == iy->getLeft()) {
            if (ix->getRight() != iy->getRight()) { failUnification(); break; }
            unificateAtoms(ix->getLeft(), ix->getAtom(), iy->getAtom(), ix->getRight());
        } else {
            if (ix->isVariable()) {
                unificateVariableAndFunction(*ix, iy, ey);
            } else { failUnification(); break; }
        }
        ++ix;
        ++iy;
    }
}

void TermUnifier::unificateAtoms(unsigned int l, const Atom& x, const Atom& y, unsigned int r) {
    const Atom *px = &x, *py = &y;

    for (int i=0; i<2; ++i) {
        if (px->isVariable()) {
            if (py->isVariable()) {
                unificateVariables(l, px->getVariable(), py->getVariable(), r); return;
            } else if (py->isConst()) {
                unificateVariableAndConstant(l, px->getVariable(), py->getConst(), r); return;
            } else if (py->isSymbol()) {
                unificateVariableAndSymbol(l, px->getVariable(), py->getSymbol(), r); return;
            }
        } else if (px->isConst()) {
            if (py->isConst()) {
                unificateConstants(l, px->getConst(), py->getConst(), r); return;
            } else if (py->isSymbol()) {
                unificateConstantAndSymbol(l, px->getConst(), py->getSymbol(), r); return;
            }
        } else if (px->isSymbol()) {
            if (py->isSymbol()) {
                unificateSymbols(l, px->getSymbol(), py->getSymbol(), r); return;
            }
        }
        std::swap(px, py);
    }
    failUnification();
}

void TermUnifier::unificateVariables(unsigned int l, const Variable& x, const Variable& y, unsigned int r) {
    if (x == y) {
        term.atoms.push_back(NestedAtom(l,x,r));
        return;
    }

    const Variable *px = &x, *py = &y;
    if (*py < *px) {
        std::swap(px, py);
    }

    lcuItems.push_back(value_ptr_type(new value_type(*px, *py)));
    term.atoms.push_back(NestedAtom(l,*px,r));
}

void TermUnifier::unificateVariableAndConstant(unsigned int l, const Variable& x, const Const& y, unsigned int r) {
    lcuItems.push_back(value_ptr_type(new value_type(x, y)));
    term.atoms.push_back(NestedAtom(l,x,r));
}

void TermUnifier::unificateVariableAndSymbol(unsigned int l, const Variable& x, const CalculationSymbol& y, unsigned int r) {
    lcuItems.push_back(value_ptr_type(new value_type(x, y)));
    term.atoms.push_back(NestedAtom(l,x,r));
}

void TermUnifier::unificateConstants(unsigned int l, const Const& x, const Const& y, unsigned int r) {
    if (x == y) {
        term.atoms.push_back(NestedAtom(l,x,r));
        return;
    }
    failUnification();
}

void TermUnifier::unificateConstantAndSymbol(unsigned int l, const Const& x, const CalculationSymbol& y, unsigned int r) {
    failUnification();
}

void TermUnifier::unificateSymbols(unsigned int l, const CalculationSymbol& x, const CalculationSymbol& y, unsigned int r) {
    if (x == y) {
        term.atoms.push_back(NestedAtom(l,x,r));
        return;
    }
    failUnification();
}

void TermUnifier::unificateVariableAndFunction(
        const NestedAtom& varAtom,
        typename atom_container::const_iterator& iy,
        typename atom_container::const_iterator& ey
        ) {
    unsigned int balance = iy->getLeft() - varAtom.getLeft();
    value_ptr_type pLcuItem(new value_type(varAtom.getVariable()));

    if (iy->getRight() >= balance) {
        if ((iy->getRight() - balance) != varAtom.getRight()) {
            failUnification(); return;
        }
        pLcuItem->term.atoms.push_back(NestedAtom(balance, iy->getAtom(), balance));
        lcuItems.push_back(pLcuItem);
        term.atoms.push_back(varAtom);
        return;
    }
    pLcuItem->term.atoms.push_back(NestedAtom(balance, iy->getAtom(), iy->getRight()));
    balance -= iy->getRight();

    while(true) {
        ++iy;
        if (iy == ey) { failUnification(); return; }
        balance += iy->getLeft();
        if (iy->getRight() >= balance) {
            if ((iy->getRight() - balance) != varAtom.getRight()) {
                failUnification(); return;
            }
            pLcuItem->term.atoms.push_back(NestedAtom(iy->getLeft(), iy->getAtom(), balance));
            lcuItems.push_back(pLcuItem);
            term.atoms.push_back(varAtom);
            return;
        }
        pLcuItem->term.atoms.push_back(NestedAtom(*iy));
        balance -= iy->getRight();
    }
}

void TermUnifier::failUnification() {
    setBad(true);
	term.clear();
	lcuItems.clear();
}

} /* namespace lem */
