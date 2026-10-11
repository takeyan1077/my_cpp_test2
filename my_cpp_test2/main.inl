#include "my_cpp_test2.hpp"

namespace MyTest {
	TestRunner runner;
	TestStates states;


	TestCase::TestCase(VoidFunc func, str name) : func(func), name(name) {
		runner.add(*this);
	}


	void TestRunner::add(TestCase test_case) {
		TestCaseList* new_test_cases = new TestCaseList {
			test_case,
			nullptr
		};
		current = new_test_cases;
		current = current->tail;
		if (!front)
			front = new_test_cases;
	}

	int TestRunner::run() {
		bool was_any_failed = false;
		while (front) {
			TestCase test_case = front->head;
			front = front->tail;

			states.reset(test_case.name);
			test_case.func();
			was_any_failed |= states.failed;
		}
		return was_any_failed;
	}


	void TestStates::log_fail() {
		if (failed) return;
		failed = true;
		std::cout << "[ FAILED \"" << test_case_name << "\" ]" << std::endl;
	}


	void output_location(size_t line, str file) {
		std::cout << file << ':' << line << std::endl;
	}

	void output_assert_name(str opename, str v1, str v2, str v3) {
		std::cout << "ASSERT" << opename << '(' << v1;
		if (*v2) std::cout << ", " << v2;
		if (*v3) std::cout << ", " << v3;
		std::cout << ')';
	}

	void output_assert_info(size_t line, str file, str opename, str v1, str v2, str v3) {
		output_assert_name(opename, v1, v2, v3);
		std::cout << " at ";
		output_location(line, file);
	}

}


int main() {
	MyTest::runner.run();
	return 0;
}
