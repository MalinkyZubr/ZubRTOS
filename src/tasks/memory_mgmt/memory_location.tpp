#include "memory.hpp"


template<typename Member>
void MemoryLocation<Member>::trigger_wrapper_delete_request(ObjectWrapper<Member> *member) {
    ATOMIC_OPERATION([this, member]() -> void {
        ObjectWrapper<Member>* deleted_wrapper = this->data_structure_delete(member);
        if(!(deleted_wrapper == nullptr)) {
            deleted_wrapper->location_transmit_object_receive_delete();
            delete deleted_wrapper;
        }}
    );
}

template<typename Member>
void MemoryLocation<Member>::graceful_destruction() {
    while(this->reference_count > 0) {}
}

template<typename Member>
MemoryLocation<Member>::~MemoryLocation() {
    this->graceful_destruction();
}