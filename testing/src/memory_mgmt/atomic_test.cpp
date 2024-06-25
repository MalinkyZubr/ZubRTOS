#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../lib/doctest.h"
#include "../../../src/board/atomic.hpp"


TEST_CASE("Testing to see if atomic operations work properly") {
    int test_var = 0;
    ATOMIC_OPERATION([&test_var]() -> void { test_var = 1; });
    CHECK(test_var == 1);
}