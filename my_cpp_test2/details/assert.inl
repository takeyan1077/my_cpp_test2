namespace MyTest {

	template <typename T>
	struct AssertExpr;

	template <typename LHS, typename RHS, typename RES>
	struct AssertExprLR {
		const LHS& left_value;
		const RHS& right_value;
		const RES& result;

		void log() const {
			output_left_right(left_value, right_value);
		}

		bool to_bool() const {
			return static_cast<bool>(result);
		}


		#define MAKE_OPERATOR(ope) \
		template <typename T> \
		auto operator ope(const T& value) { \
			return AssertExprLR {result, value, result ope value}; \
		}
		MAKE_OPERATOR(==) 
		MAKE_OPERATOR(!=)
		MAKE_OPERATOR(<)
		MAKE_OPERATOR(<=)
		MAKE_OPERATOR(>)
		MAKE_OPERATOR(>=)
		MAKE_OPERATOR(||) 
		MAKE_OPERATOR(&&)
		#undef MAKE_OPERATOR

		#define MAKE_OPERATOR(ope) \
		template <typename T> \
		auto operator ope(const T& value) { \
			return AssertExpr {result ope value}; \
		}
		MAKE_OPERATOR(&)
		MAKE_OPERATOR(|)
		MAKE_OPERATOR(^)
		#undef MAKE_OPERATOR
	};


	template <typename T>
	struct AssertExpr {
		const T& value;

		void log() {}

		bool to_bool() {
			return static_cast<bool>(value);
		}

		#define MAKE_OPERATOR(ope) \
		template <typename U> \
		auto operator ope(const U& other) { \
			return AssertExprLR{value, other, value ope other}; \
		}
		MAKE_OPERATOR(==)
		MAKE_OPERATOR(!=)
		MAKE_OPERATOR(<)
		MAKE_OPERATOR(<=)
		MAKE_OPERATOR(>)
		MAKE_OPERATOR(>=)
		MAKE_OPERATOR(||)
		MAKE_OPERATOR(&&)
		#undef MAKE_OPERATOR

		#define MAKE_OPERATOR(ope) \
		template <typename U> \
		auto operator ope(const U& other) { \
			return AssertExpr {value ope other}; \
		}
		MAKE_OPERATOR(&)
		MAKE_OPERATOR(|)
		MAKE_OPERATOR(^)
		#undef MAKE_OPERATOR
	};


	struct AssertStart {
		template <typename T>
		AssertExpr<T> operator<(const T& value) {
			return AssertExpr{value};
		}
	};
}


#define ASSERT_EQ(left, right) do { \
auto left_value = left; auto right_value = right; \
if (!(left_value == right_value)) { \
	MyTest::states.log_fail(); \
	MyTest::output_assert_info(__LINE__, __FILE__, "_EQ", #left, #right); \
	MyTest::output_left_right(left, right); \
	return; \
} } while(0)


#define ASSERT_NE(left, right) do { \
auto left_value = left; auto right_value = right; \
if (!(left_value != right_value)) { \
	MyTest::states.log_fail(); \
	MyTest::output_assert_info(__LINE__, __FILE__, "_EQ", #left, #right); \
	MyTest::output_left_right(left, right); \
	return; \
} } while(0)


#define ASSERT(expr) do { \
auto result_of_assertion = MyTest::AssertStart() < expr; \
if (!result_of_assertion.to_bool()) { \
	MyTest::states.log_fail(); \
	MyTest::output_assert_info(__LINE__, __FILE__, "", #expr); \
	result_of_assertion.log(); \
	return; \
} } while(0)
