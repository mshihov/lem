/*
 * TermUnifier.h
 *
 *  Created on: 18.08.2012
 *      Author: solo
 */

#ifndef TERMUNIFIER_H_
#define TERMUNIFIER_H_

#include "Term.h"
#include "Lcu.h"

namespace lem {

class TermUnifier {
public:
    TermUnifier(const Term& x, const Term& y) {doUnification(x, y);}
    ~TermUnifier() {}

    const Term getTerm() {return term;}
    const Lcu getLcu() {return lcu;}

private:
    Term term;
    Lcu  lcu;

    void doUnification(const Term& x, const Term& y);
    void failUnification();
    void unificateAtoms(unsigned int l, const Atom& x, const Atom& y, unsigned int r);
    void unificateFunction(
            const Variable& x,
            typename Term::atom_container::const_iterator& iy,
            typename Term::atom_container::const_iterator& ey
            );
};

} /* namespace lem */
#endif /* TERMUNIFIER_H_ */
