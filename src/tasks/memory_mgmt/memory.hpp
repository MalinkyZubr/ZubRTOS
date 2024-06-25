#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "../../board/atomic.hpp"

template<typename Wrapped>
class MemorySafeObject;


template<typename Member>
class MemoryLocation;


template<typename Wrapped>
class ObjectWrapper {
    private:
        MemorySafeObject<Wrapped> *associated_object;
        MemoryLocation<Wrapped> *memory_location;

        // for use by the memory safe object
        ObjectWrapper *next_internal_wrapper = nullptr;

        // for use by shared memory location
        ObjectWrapper *next_wrapper = nullptr;
        ObjectWrapper *previous_wrapper = nullptr;
    public:
        ObjectWrapper(MemorySafeObject<Wrapped> *object, MemoryLocation<Wrapped> *location);

        MemorySafeObject<Wrapped>* get_memory_safe();
        Wrapped* get_wrapped();
        MemorySafeObject<Wrapped>* get_associated_object();

        // for use by the safe memory objectWrapped
        ObjectWrapper<Wrapped>* get_next_internal_wrapper(MemorySafeObject<Wrapped> *requester);
        void set_next_internal_wrapper(MemorySafeObject<Wrapped> *requester, ObjectWrapper<Wrapped> *next);

        // for use by the shared memory location
        ObjectWrapper<Wrapped>* next();
        ObjectWrapper<Wrapped>* previous();
        void set_next(ObjectWrapper<Wrapped> *next); 
        void set_previous(ObjectWrapper<Wrapped> *previous);

        // deletion operations
        void location_transmit_object_receive_delete();
        void object_transmit_location_receive_delete();
};


template<typename Member> 
class SharedMemoryStructure {
    protected:
        int reference_count = 0;
        void ref_count_increment();
        void ref_count_decrement();
        virtual ObjectWrapper<Member>* data_structure_delete(ObjectWrapper<Member> *member) {};
        virtual void graceful_destruction() {};
    public:
        void receive_wrapper_delete_request(ObjectWrapper<Member> *member);
        virtual void trigger_wrapper_delete_request(ObjectWrapper<Member> *member) {};
};


template<typename Member> // SHOULD ONLY BE DELETED WHEN REFERENCE COUNTER REACHES 0
class MemoryLocation : public SharedMemoryStructure<Member> { // this is where the actual data goes. This is a template datastructure
    protected:
        ObjectWrapper<Member> *start = nullptr;
        virtual ObjectWrapper<Member>* data_structure_delete(ObjectWrapper<Member> *member) {};
        void graceful_destruction();
    public:
        virtual ObjectWrapper<Member>* get_wrapper(Member *member) {};
        virtual void push_member(ObjectWrapper<Member> *member) {};
        void trigger_wrapper_delete_request(ObjectWrapper<Member> *member);

        ~MemoryLocation();
};


template<typename Wrapped> // THIS SHOULD ONLY BE DELETED WHEN THE REFERENCE COUNTER REACHES 0
class MemorySafeObject : public SharedMemoryStructure<Wrapped> { // this is the object's main storage area
    public:      
        MemorySafeObject(Wrapped *object);

        Wrapped* get_wrapped_object();
        void generate_wrapper(MemoryLocation<Wrapped> *wrapper_storage);
        void trigger_wrapper_delete_request(ObjectWrapper<Wrapped> *member);

        ~MemorySafeObject();

    private:
        ObjectWrapper<Wrapped> *first_reference = nullptr;
        Wrapped *wrapped_object;

    protected:
        ObjectWrapper<Wrapped>* data_structure_delete(ObjectWrapper<Wrapped> *wrapper);
        void graceful_destruction();
        void delete_all_wrappers();
        void delete_single_wrapper(ObjectWrapper<Wrapped> *selected_wrapper, ObjectWrapper<Wrapped> *previous_wrapper, ObjectWrapper<Wrapped> *next_wrapper);
};


#include "shared_memory_structure.tpp"
#include "memory_safe_obj.tpp"
#include "memory_location.tpp"
#include "object_wrapper.tpp"


#endif