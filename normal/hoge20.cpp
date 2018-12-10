#include <iostream>

template <uint64_t N>
struct binary_impl {
	static const uint64_t value = binary_impl<N/10>::value * 2 + N%10;
};

template <>
struct binary_impl<0> {
	static const uint64_t value = 0;
};


auto main() -> int {

	std::cout << "result : " << binary_impl<1011u>::value << std::endl;

	return 0;
}

