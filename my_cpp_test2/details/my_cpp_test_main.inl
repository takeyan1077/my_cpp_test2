#include "../my_cpp_test2.hpp"

namespace MyTest {
	TestRunner runner;
	TestStates states;


	TestCase::TestCase(VoidFunc func, str name, size_t line, str filename) 
		: func(func), name(name), line(line), file(filename) {
		runner.add(*this);
	}


	void TestRunner::add(TestCase test_case) {
		TestCaseList* new_test_cases = new TestCaseList {
			test_case,
			nullptr
		};
		if (!front) {
			front = new_test_cases;
			current = new_test_cases;
		}
		current->tail = new_test_cases;
		current = current->tail;
	}


	int TestRunner::run() {
		int done_count = 0;
		int failed_count = 0;
		while (front) {
			TestCase test_case = front->head;
			front = front->tail;

			states.reset(test_case);
			test_case.func();
			if (states.failed) {
				failed_count++;
				std::cout << '\n';
			}
			done_count++;
		}
		const bool was_failed = failed_count != 0;
		std::cout << "================================================\n";
		std::cout << "done: " << done_count
			<< "  failed: " << failed_count
			<< "  passed: " << done_count - failed_count << std::endl;
		std::cout << (was_failed ? "TEST FAILED\n" : "all test passed\n");

		return failed_count != 0;
	}


	void TestStates::log_fail() {
		if (failed) return;
		failed = true;
		std::cout << "[ FAILED \"" << test_case_name << "\" at ";
		output_location(line, file);
		std::cout << " ]" << std::endl;
	}


	void output_location(size_t line, str file) {
		std::cout << file << ':' << line;
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
		std::cout << std::endl;
	}

}


int main() {
	return MyTest::runner.run();
}
