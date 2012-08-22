/*
 * Value.cpp
 *
 *  Created on: 28.07.2012
 *      Author: solo
 */

#include "CalculationSymbol.h"
#include<iostream>

namespace lem {

CalculationSymbol::CalculationSymbol(const CalculationSymbol& v) {
    switch (v.type) {
    case INT: makeInt(v.mem.intValue); break;
    case FLOAT: makeFloat(v.getFloat()); break;
    case STRING: makeString(v.getString()); break;
    }
}


CalculationSymbol::~CalculationSymbol() {
    switch (type) {
    case INT: killInt(); break;
    case FLOAT: killFloat(); break;
    case STRING: killString(); break;
    }
}

void CalculationSymbol::makeInt(int i) { type = INT; mem.intValue = i; }

void CalculationSymbol::makeFloat(float f) { type = FLOAT; mem.valueBuf = new float(f); }

void CalculationSymbol::makeString(const std::string& s) { type = STRING; mem.valueBuf = new std::string(s); }

void CalculationSymbol::killInt() {}

void CalculationSymbol::killFloat() { delete (float*)mem.valueBuf; mem.valueBuf = 0; }

void CalculationSymbol::killString() { delete (std::string*)mem.valueBuf; mem.valueBuf = 0; }

} /* namespace lem */
