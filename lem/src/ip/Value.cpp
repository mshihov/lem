/*
 * Value.cpp
 *
 *  Created on: 28.07.2012
 *      Author: solo
 */

#include "Value.h"
#include<iostream>

namespace lem {

Value::Value(const Value& v) {
    type = v.type;
    // TODO
}

Value::~Value() {
    if (type == INT) {
    } else if (type == FLOAT) {
    } else if (type == STRING) {
    }
}

} /* namespace lem */
