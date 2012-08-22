/*
 * Lcu.cpp
 *
 *  Created on: 17.08.2012
 *      Author: solo
 */

#include "Lcu.h"

namespace lem {

void Lcu::setInconsistent() {
	inconsistent = true;
	vals.clear();
	evals.clear();
}


} /* namespace lem */
