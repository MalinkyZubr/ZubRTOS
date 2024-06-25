#include "test_location.hpp"


void TestLocation::push_member(ObjectWrapper<TestMember> *member) {
    this->start = member;
}

ObjectWrapper<TestMember>* TestLocation::data_structure_delete(ObjectWrapper<TestMember> *member) {
    ObjectWrapper<TestMember> *temp = this->start;
    this->start = nullptr;
    return temp;
}

ObjectWrapper<TestMember>* TestLocation::get_wrapper(TestMember *member) {
    return this->start;
}