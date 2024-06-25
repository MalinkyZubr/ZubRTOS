#ifndef ATOMIC_H
#define ATOMIC_H

//#include <Arduino.h>

#define ATOMIC_TEST 1

#ifndef cli
#define cli() {}
#endif

#ifndef sei
#define sei() {}
#endif


template<typename Func>
void ATOMIC_OPERATION(Func func);

#include "atomic.tpp"

#endif