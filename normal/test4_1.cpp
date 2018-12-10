#include <iostream>


template <size_t N>
struct factorial {
	static const size_t value = N * factorial<N-1>::value;
};

// explicit specialization / full specialization
template <>
struct factorial<0> {
	static const size_t value = 1;
};


// 古いコンパイラだとメンバ定数を表すのにenumしか使えない
// => enum hack
template <size_t N>
struct factorial_enum {
	enum { value = N * factorial_enum<N-1>::value };
};

// explicit specialization / full specialization
template <>
struct factorial_enum<0> {
	enum { value = 1 };
};



auto main() -> int {
	constexpr size_t NUM = 5;
	std::cout << NUM << " : " << factorial<NUM>::value << std::endl;

	constexpr size_t NUM2 = 3;
	std::cout << NUM2 << " : " << factorial_enum<NUM2>::value << std::endl;

	return 0;
}

