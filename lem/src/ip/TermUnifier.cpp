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
    typename Term::atom_container::const_iterator ix = x.atoms.begin();
    typename Term::atom_container::const_iterator ex = x.atoms.end();

    typename Term::atom_container::const_iterator iy = y.atoms.begin();
    typename Term::atom_container::const_iterator ey = y.atoms.end();

    do {
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
                unificateFunction(ix->getVariable(), iy, ey);
            } else { failUnification(); break; }
        }
        ++ix;
        ++iy;
    } while(true);
}

void TermUnifier::unificateAtoms(unsigned int l, const Atom& x, const Atom& y, unsigned int r) {
    //TODO c-c, v-v, s-s, v-c, v-s
}

void TermUnifier::unificateFunction(
        const Variable& x,
        typename Term::atom_container::const_iterator& iy,
        typename Term::atom_container::const_iterator& ey
        ) {
    //TODO v-t
}

void TermUnifier::failUnification() {
	term.erase();
	lcu.setInconsistent();
}

} /* namespace lem */
