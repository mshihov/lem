/*
 * Ptr.h
 *
 *  Created on: 24.08.2012
 *      Author: solo
 */

#ifndef PTR_H_
#define PTR_H_

#include<utility>

namespace lem {

template<class T>
class Ptr {
public:
    explicit Ptr(T *p);
    Ptr(const Ptr& p);
    Ptr& operator=(const Ptr& p);
    T* operator->() const;
    T& operator*() const;
    ~Ptr();
private:
    Ptr();
    std::pair<unsigned int, T*> *meta;
    void release();
};

template<class T>
Ptr<T>::Ptr(T *p) {
    meta = new std::pair<unsigned int, T*>(1, p);
}

template<class T>
Ptr<T>::Ptr():meta(0) {}

template<class T>
Ptr<T>::Ptr(const Ptr<T>& p) {
    meta = p.meta;
    if (meta != 0) {
        meta->first++;
    }
}

template<class T>
Ptr<T>& Ptr<T>::operator= (const Ptr& p) {
    if (meta == p.meta) {
        if (meta != 0 && this != &p) {
            meta->first++;
        }
    } else {
        if (meta != 0) {
            release();
        }
        meta = p.meta;
        if (meta != 0) {
            meta->first++;
        }
    }
    return *this;
}

template<class T>
T* Ptr<T>::operator->() const {
    return meta->second;
}

template<class T>
T& Ptr<T>::operator*() const {
    return *(meta->second);
}

template<class T>
Ptr<T>::~Ptr() {
    release();
}

template<class T>
void Ptr<T>::release() {
    if (meta != 0) {
        meta->first--;
        if (meta->first == 0) {
            delete meta->second;
            meta->second = 0;
            delete meta;
        }
        meta = 0;
    }
}

} /* namespace lem */
#endif /* PTR_H_ */
