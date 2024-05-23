#include "memory.hpp"


template<typename Wrapped>
MemorySafeObject<Wrapped>::MemorySafeObject(Wrapped *object) : wrapped_object(object) {}


template<typename Wrapped>
Wrapped *MemorySafeObject<Wrapped>::get_wrapped_object() {
    return this->wrapped_object;
}


template<typename Wrapped>
void MemorySafeObject<Wrapped>::generate_wrapper(MemoryLocation<Wrapped> *wrapper_storage) {
    ObjectWrapper<Wrapped> *new_wrapper = new ObjectWrapper<Wrapped>(this, wrapper_storage);
    ObjectWrapper<Wrapped> *selected_wrapper= this->first_reference;

    if(selected_wrapper == nullptr) {
        this->first_reference = new_wrapper;
    }
    else {
        while(selected_wrapper->get_next_internal_wrapper(this) != nullptr) {
            selected_wrapper = selected_wrapper->get_next_internal_wrapper(this);
        }
        selected_wrapper->set_next_internal_wrapper(this, new_wrapper);
    }
}


template<typename Wrapped>
void MemorySafeObject<Wrapped>::safe_wrapper_delete(ObjectWrapper<Wrapped> *wrapper) {
    ObjectWrapper<Wrapped> *previous_wrapper = nullptr;
    ObjectWrapper<Wrapped> *selected_wrapper = this->first_reference;
    ObjectWrapper<Wrapped> *next_wrapper = nullptr;

    while(wrapper != selected_wrapper && selected_wrapper != nullptr) {
        previous_wrapper = selected_wrapper;
        selected_wrapper = next_wrapper;
        next_wrapper = selected_wrapper->get_next_internal_wrapper(this);
    }
    if(selected_wrapper != nullptr) {
        if(previous_wrapper != nullptr) {
            previous_wrapper->set_next_internal_wrapper(this, next_wrapper);
        }
        else {
            this->first_reference = next_wrapper;
        }
    }
}


template<typename Wrapped>
MemorySafeObject<Wrapped>::~MemorySafeObject() {
    ObjectWrapper<Wrapped> *selected_wrapper= this->first_reference;
    ObjectWrapper<Wrapped> *next_wrapper= nullptr;

    while(selected_wrapper != nullptr) {
        next_wrapper = selected_wrapper->get_next_internal_wrapper(this);
        delete selected_wrapper;
        selected_wrapper = next_wrapper;
    }
}