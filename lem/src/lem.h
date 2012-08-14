/*
 * lem.h
 *
 *  Created on: 14.08.2012
 *      Author: mirrlis
 */

#ifndef LEM_H_
#define LEM_H_

namespace lem {

template <class T> inline bool operator>(const T& x, const T& y) {
	return y < x;
}

template <class T> inline bool operator!=(const T& x, const T& y) {
	return !(y == x);
}

template <class T> inline bool operator<=(const T& x, const T& y) {
	return !(y < x);
}

template <class T> inline bool operator>=(const T& x, const T& y) {
	return !(x < y);
}

} /* namespace lem */

#endif /* LEM_H_ */
