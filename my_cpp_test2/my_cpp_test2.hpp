#pragma once
#include <iostream>

namespace MyTest {

	using VoidFunc = void(*)();
	using str = const char*;

	struct TestCase {
		VoidFunc func;
		str name;
		size_t line;
		str file;

		TestCase(VoidFunc func, str name, size_t line, str filename);
	};


	class TestRunner {
	private:
		struct TestCaseList {
			TestCase head;
			TestCaseList* tail;
		};

		TestCaseList* current = nullptr;
		TestCaseList* front = nullptr;
		
	public:
		void add(TestCase test_case);
		int run();
	};
	
	
	struct TestStates {
		bool failed = false;
		str test_case_name = nullptr;
		size_t line;
		str file;

		void reset(const TestCase& test_case) {
			failed = false;
			test_case_name = test_case.name;
			line = test_case.line;
			file = test_case.file;
		}

		void log_fail();
	};


	template <typename T>
	concept can_output = requires(T a) {
		std::cout << a;
	};

	template <typename L, typename R>
	void output_left_right(const L& left, const R& right) {
		if constexpr (can_output<L>) {
			std::cout << "  left: " << left;
		}
		if constexpr (can_output<R>) {
			std::cout << "  right: " << right;
		}
		std::cout << std::endl;
	}

	void output_location(size_t line, str file);
	void output_assert_name(str opename, str v1 = "", str v2 = "", str v3 = "");
	void output_assert_info(size_t line, str file, str opename, str v1 = "", str v2 = "", str v3 = "");

	extern TestRunner runner;
	extern TestStates states;


} // namespace MyTest;


#define CONCAT_IMPL(x, y) x ## y
#define CONCAT(x, y) CONCAT_IMPL(x, y)


#define TEST_CASE_IMPL(testname, funcname, objname) \
namespace MyTestFuncs { static void funcname(); \
static MyTest::TestCase objname(funcname, testname, __LINE__, __FILE__); } \
static void MyTestFuncs::funcname()

#define TEST_CASE(name) TEST_CASE_IMPL(name, CONCAT(test_func_, __COUNTER__), CONCAT(test_obj_, __COUNTER__))


#include "details/assert.inl"

#ifdef MY_TEST_MAIN
	#include "details/my_cpp_test_main.inl"
#endif
