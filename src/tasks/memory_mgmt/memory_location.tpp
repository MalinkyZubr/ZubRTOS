#include "memory.hpp"


template<typename Member>
MemoryLocation<Member>::~MemoryLocation() {
    
}


template<typename Member>
void MemoryLocation<Member>::trigger_wrapper_delete_request(ObjectWrapper<Member> *member) {
    ATOMIC_OPERATION([]() -> void {
        ObjectWrapper<Member> deleted_wrapper = this->data_structure_delete(member);
        if(deleted_wrapper != nullptr) {
            deleted_wrapper->location_transmit_object_receive_delete();
            delete deleted_wrapper;
        }}
    );
}