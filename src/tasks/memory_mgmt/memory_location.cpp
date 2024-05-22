#include "memory.hpp"


template<typename Member>
MemoryLocation<Member>::~MemoryLocation() {
    this->graceful_delete();
}