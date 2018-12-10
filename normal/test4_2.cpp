#include <iostream>

// enum hack
template <int N>
struct square {
	enum { value = N * N };
};

// Exponential function.
template <int N, int i>
struct pow {
	static const int value = N * pow<N,i-1>::value;
};

// full specialization / explicit specialization
template <int N>
struct pow<N,0> {
	static const int value = 1;
};


int main() {
	constexpr size_t N = 6;

	std::cout << N << " : " << square<N>::value << std::endl;

	constexpr size_t i = 3;
	std::cout << N << "^" << i << " : " << pow<N,i>::value << std::endl;

	return 0;
}

