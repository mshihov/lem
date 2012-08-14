/*
 * Value.h
 *
 *  Created on: 28.07.2012
 *      Author: solo
 */

#ifndef VALUE_H_
#define VALUE_H_

#include "../lem.h"
#include<string>

namespace lem {

//TODO share pointer on complex values (string...)
class Value {
public:
    Value(int   value) {type = INT; mem.intValue = value;};
    Value(float value);
    Value(const std::string& value);
    Value(const Value& value);

    ~Value(); //TODO need explicit destructor call for complex types

    int getInt() const {return mem.intValue;};
    float getFloat() const {return *((float*)mem.valueBuf);};
    const std::string& getString() const {return *((std::string*)mem.intValue);}; //TODO
private:
    enum {INT, FLOAT, STRING} type;
    union {
        int intValue;
        void *valueBuf;
    } mem;
};

} /* namespace lem */
#endif /* VALUE_H_ */
