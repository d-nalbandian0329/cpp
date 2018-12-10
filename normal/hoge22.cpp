#include <iostream>
#include <array>
#include <string>

template <int N>
struct FizzBuzz {
	static std::array<const std::string, 4> str = {
		std::string("FizzBuzz"),
		std::string("Fizz"),
		std::string("Buzz"),
		std::string(N)
	};

	static const std::string value
			= str[(!(N%15)&&(N/15) ? 0 : (!(N%3)&&(N/3) ? 1 : (!(N%5)&&(N/5) ? 2 : 3)))];
};


auto main() -> int {
//	for(int i = 0; i <= 30; ++i)
//		std::cout << i << FizzBuzz<i>::value << std::endl;
	constexpr int N = 15;

	std::cout << N << FizzBuzz<N>::value << std::endl;

	return 0;
}

