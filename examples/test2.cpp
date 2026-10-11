#include "my_cpp_test2/my_cpp_test2.hpp"

int mul(int a, int b) {
	return a * b;
}


TEST_CASE("test mul 2") {
	ASSERT(mul(1, 4));
}


TEST_CASE("test mul") {
	ASSERT(2 == mul(1, 2));
	ASSERT(mul(2, 3) == 6);
	ASSERT(mul(2, 3) < 7);
	ASSERT(mul(100, 20) == 0);
}

TEST_CASE("test mul 3") {
	ASSERT(mul(9, 0));
}
