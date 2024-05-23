#include "test_location.hpp"


void TestLocation::push_member(ObjectWrapper<TestMember> *member) {
    this->start = member;
}

void TestLocation::delete_member(ObjectWrapper<TestMember> *member) {
    delete member;
    this->start = nullptr;
}

void TestLocation::graceful_delete() {
    this->delete_member(this->start);
}

ObjectWrapper<TestMember>* TestLocation::get_wrapper(TestMember *member) {
    return this->start;
}