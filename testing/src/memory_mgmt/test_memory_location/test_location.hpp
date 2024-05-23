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
        void delete_member(ObjectWrapper<TestMember> *member) override;
        void graceful_delete() override;
};


#endif