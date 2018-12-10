#include <iostream>
#include <string>
#include <sstream>

std::string fizzbuzz(int N) {
	std::stringstream ss;
	std::string num;

	ss << N;
	ss >> num;

	return (!(N%15) ? "FizzBuzz" : (!(N%3) ? "Fizz" : (!(N%5) ? "Buzz" : num)));
}


auto main() -> int {
	for(int i = 1; i <= 30; ++i)
		std::cout << i << " : " << fizzbuzz(i) << std::endl;

	return 0;
}

