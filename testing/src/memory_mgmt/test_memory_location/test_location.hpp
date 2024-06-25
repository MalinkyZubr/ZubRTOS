#ifndef TEST_LOCATION_HPP
#define TEST_LOCATION_HPP

#include "../../../../src/tasks/memory_mgmt/memory.hpp"


class TestMember {
    public:
    int number = 5;
};


class TestLocation : public MemoryLocation<TestMember> {
    public:
        ObjectWrapper<TestMember>* get_wrapper(TestMember *member) override;
        void push_member(ObjectWrapper<TestMember> *member) override;
        ObjectWrapper<TestMember>* get_first(TestMember *member);
    protected:
        ObjectWrapper<TestMember>* data_structure_delete(ObjectWrapper<TestMember> *member) override;
};


#endif