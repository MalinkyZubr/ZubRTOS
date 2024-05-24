#include "atomic.h"


template<typename Func>
void ATOMIC_OPERATION(Func func) {
    if(ATOMIC_TEST == 0) {
        noInterrupts();
        f();
        interrupts();
    }
    else {
        f();
    }
}