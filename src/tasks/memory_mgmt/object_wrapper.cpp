#include "memory.hpp"


template<typename Wrapped>
ObjectWrapper<Wrapped>::ObjectWrapper(MemorySafeObject<Wrapped> *object, MemoryLocation<Wrapped> *location) {
    location->push_member(this);
}

template<typename Wrapped>
ObjectWrapper<Wrapped> ObjectWrapper<Wrapped>::next() {
    return this->next_wrapper;
}


template<typename Wrapped>
void ObjectWrapper<Wrapped>::set_next(ObjectWrapper<Wrapped> *next) {
    this->next_wrapper = next;
}


template<typename Wrapped>
MemorySafeObject<Wrapped> ObjectWrapper<Wrapped>::get_memory_safe() {
    return this->associated_object;
}

template<typename Wrapped>
Wrapped ObjectWrapper<Wrapped>::get_wrapped() {
    return this->associated_object->get_wrapped_object();
}


template<typename Wrapped>
ObjectWrapper<Wrapped>::~ObjectWrapper() {
    this->memory_location->delete_member(this);
}