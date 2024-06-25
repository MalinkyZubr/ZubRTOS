#include "atomic.hpp"


template<typename Func>
void ATOMIC_OPERATION(Func func) {
    if(ATOMIC_TEST == 0) {
        cli();
        func();
        sei();
    }
    else {
        func();
    }
}