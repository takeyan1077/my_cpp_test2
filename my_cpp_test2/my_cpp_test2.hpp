#pragma once
#include <iostream>

namespace MyTest {

	using VoidFunc = void(*)();
	using str = const char*;

	struct TestCase {
		VoidFunc func;
		str name;

		TestCase(VoidFunc func, str name);
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

		void reset(str new_test_case_name) {
			failed = false;
			test_case_name = new_test_case_name;
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
			std::cout << "    left: " << left;
		}
		if constexpr (can_output<R>) {
			std::cout << "    right: " << right;
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
namespace MyTestFuncs { static void funcname(); static MyTest::TestCase objname {funcname, testname}; } \
static void MyTestFuncs::funcname()

#define TEST_CASE(name) TEST_CASE_IMPL(name, CONCAT(test_func_, __COUNTER__), CONCAT(test_obj_, __COUNTER__))


#define ASSERT_EQ(left, right) do { \
auto left_value = left; auto right_value = right; \
if (!(left_value == right_value)) { \
	MyTest::states.log_fail(); \
	MyTest::output_assert_info(__LINE__, __FILE__, "_EQ", #left, #right); \
	MyTest::output_left_right(left, right); \
	return; \
} \
} while(0)



#ifdef MY_TEST_MAIN
	#include "main.inl"
#endif
