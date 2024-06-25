#include "memory.hpp"
#include <iostream>


template<typename Member> // must assume that the operation is already atomic
void SharedMemoryStructure<Member>::receive_wrapper_delete_request(ObjectWrapper<Member> *member) {
    ATOMIC_OPERATION([this, member]() -> void {
        this->data_structure_delete(member);
        this->ref_count_decrement();
    });
}


template<typename Member>
void SharedMemoryStructure<Member>::ref_count_increment() {
    this->reference_count++;
}


template<typename Member>
void SharedMemoryStructure<Member>::ref_count_decrement() {
    this->reference_count--;
}