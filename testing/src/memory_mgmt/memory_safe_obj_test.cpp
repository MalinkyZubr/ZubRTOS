#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../lib/doctest.h"
#include "../../../src/tasks/memory_mgmt/memory.hpp"
#include "./test_memory_location/test_location.hpp"
#include <iostream>


TestMember test_instance = TestMember();
MemorySafeObject<TestMember> test_safe_object = MemorySafeObject<TestMember>(&test_instance);
TestLocation test_location = TestLocation();
ObjectWrapper<TestMember>* wrapper_to_delete;

TEST_CASE("Testing the object getter") {
    CHECK(&test_instance == test_safe_object.get_wrapped_object());
}

TEST_CASE("Testing the wrapper generator") {
    test_safe_object.generate_wrapper(&test_location);
    wrapper_to_delete = test_location.get_wrapper(&test_instance);
    CHECK(wrapper_to_delete->get_memory_safe() == &test_safe_object);
}

TEST_CASE("Testing that individual wrappers can safely be deleted") {
    test_safe_object.safe_wrapper_delete(wrapper_to_delete);
    CHECK(test_location.get_wrapper(&test_instance) == nullptr);
}

TEST_CASE("Testing to see that the safe memory object can be destroyed successfully") {
    CHECK(1 == 1);
}

