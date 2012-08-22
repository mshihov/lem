/*
 * Value.h
 *
 *  Created on: 28.07.2012
 *      Author: solo
 */

#ifndef CALCULATION_SYMBOL_H_
#define CALCULATION_SYMBOL_H_

#include "../lem.h"
#include<string>

namespace lem {

//TODO share pointer on complex values (string...) now is deep copying
class CalculationSymbol {
public:
    CalculationSymbol(int i) { makeInt(i); }
    CalculationSymbol(float f) { makeFloat(f); }
    CalculationSymbol(const std::string& s) { makeString(s); }
    CalculationSymbol(const CalculationSymbol& value);

    ~CalculationSymbol(); //TODO need explicit destructor call for complex types

    int getInt() const {return mem.intValue;};
    float getFloat() const {return *((float*)mem.valueBuf);};
    const std::string& getString() const {return *((std::string*)mem.intValue);}; //TODO
private:
    enum {INT, FLOAT, STRING} type;
    union {
        int intValue; //store int values explicitly
        void *valueBuf; //
    } mem;

    void makeInt(int i);
    void makeFloat(float f);
    void makeString(const std::string& s);

    void killInt();
    void killFloat();
    void killString();
};

} /* namespace lem */

#endif /* CALCULATION_SYMBOL_H_ */
