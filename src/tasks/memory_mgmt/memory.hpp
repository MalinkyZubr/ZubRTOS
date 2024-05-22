#ifndef MEMORY_HPP
#define MEMORY_HPP


template<typename Wrapped>
class MemorySafeObject;


template<typename Member>
class MemoryLocation;


template<typename Wrapped>
class ObjectWrapper {
    private:
        const MemorySafeObject<Wrapped> *associated_object;
        const MemoryLocation *memory_location;

        // for use by the memory safe object
        ObjectWrapper *next_internal_wrapper = nullptr;

        // for use by shared memory location
        ObjectWrapper *next_wrapper = nullptr;
        ObjectWrapper *previous_wrapper = nullptr;
    public:
        ObjectWrapper(MemorySafeObject<Wrapped> *object, MemoryLocation<Wrapped> *location);
        MemorySafeObject<Wrapped> get_memory_safe();
        Wrapped get_wrapped();

        // for use by the safe memory object
        ObjectWrapper<Wrapped>* get_next_internal_wrapper(MemorySafeObject<Wrapped> *requester);
        void set_next_internal_wrapper(MemorySafeObject<Wrapped> *requester, ObjectWrapper<Wrapped> *next);

        // for use by the shared memory location
        ObjectWrapper<Wrapped>* next();
        ObjectWrapper<Wrapped>* previous();
        void set_next(ObjectWrapper<Wrapped> *next); 
        void set_previous(ObjectWrapper<Wrapped> *previous);
        ~ObjectWrapper();
};


template<typename Member>
class MemoryLocation { // this is where the actual data goes. This is a template datastructure
    protected:
        ObjectWrapper<Member> *start = nullptr;
    public:
        virtual void push_member(ObjectWrapper<Member> *member);
        virtual void delete_member(ObjectWrapper<Member> *member);
        virtual void graceful_delete();
        ~MemoryLocation() {};
};


template<typename Wrapped>
class MemorySafeObject { // this is the object's main storage area
    public:      
        MemorySafeObject(Wrapped *object);
        Wrapped get_wrapped_object();
        void generate_wrapper(MemoryLocation<Wrapped> *wrapper_storage);
        void safe_wrapper_delete(ObjectWrapper<Wrapped> *wrapper);
        ~MemorySafeObject();

    private:
        ObjectWrapper<Wrapped> *first_reference = nullptr;
        Wrapped *wrapped_object;
};


#endif