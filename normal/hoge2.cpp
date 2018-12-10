#include <iostream>
#include <iterator>
#include <algorithm>

/*
template <class T, class... Args>
void print(Args... args) {
	T ary[] = { args... };

	std::copy(std::begin(ary), std::end(ary), std::ostream_iterator<T>(std::cout, ','));
	std::cout << std::endl;
}
*/


int main() {
	//print(1, 2, 3, 4);

	int ary[] = { 1, 2, 3, 4 };

	std::copy(std::begin(ary), std::end(ary), std::ostream_iterator<int>(std::cout, ","));

	std::cout << std::endl;
}

