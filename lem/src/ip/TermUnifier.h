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
    TermUnifier(const Term& x, const Term& y);
    ~TermUnifier() {}

    const Term getTerm() {return term;}
    const Lcu getLcu() {return lcu;}
private:
    Term term;
    Lcu  lcu;
};

} /* namespace lem */
#endif /* TERMUNIFIER_H_ */
