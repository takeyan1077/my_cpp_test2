#define MY_TEST_MAIN
#include "my_cpp_test2/my_cpp_test2.hpp"


TEST_CASE("test case") {
	ASSERT_EQ(0, 0);
	ASSERT(1 == 0);
}


int add(int a, int b) {
	return a + b;
}


TEST_CASE("test add") {
	ASSERT(add(2, 5) == 7);
	ASSERT(add(5, 4) == 8);
}

TEST_CASE("test add 2") {
	ASSERT(add(-1, -3));
}
