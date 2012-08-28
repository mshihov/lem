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
    typedef typename Lcu::value_container value_container;

    TermUnifier(const Term& x, const Term& y) {doUnification(x, y);}
    ~TermUnifier() {}

    const Term &getTerm() const {return term;}
    const value_container &getUnifiers() const {return unifiers;}

    bool isUnificationFailed() {return (term.atoms.size() == 0);}
    bool termsIsEquals() {return (unifiers.size() == 0);}
private:
    typedef typename Term::atom_container atom_container;

    Term term;
    value_container unifiers;

    void doUnification(const Term& x, const Term& y);
    void failUnification();
    void unificateAtoms(unsigned int l, const Atom& x, const Atom& y, unsigned int r);
    void unificateVariableAndFunction(
            const NestedAtom& x,
            typename atom_container::const_iterator& iy,
            typename atom_container::const_iterator& ey
            );
    void unificateVariables(unsigned int l, const Variable& x, const Variable& y, unsigned int r);
    void unificateVariableAndConstant(unsigned int l, const Variable& x, const Const& y, unsigned int r);
    void unificateVariableAndSymbol(unsigned int l, const Variable& x, const CalculationSymbol& y, unsigned int r);
    void unificateConstants(unsigned int l, const Const& x, const Const& y, unsigned int r);
    void unificateConstantAndSymbol(unsigned int l, const Const& x, const CalculationSymbol& y, unsigned int r);
    void unificateSymbols(unsigned int l, const CalculationSymbol& x, const CalculationSymbol& y, unsigned int r);
};

} /* namespace lem */
#endif /* TERMUNIFIER_H_ */
