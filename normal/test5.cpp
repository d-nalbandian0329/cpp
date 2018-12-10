#include <iostream>
#include <cstring>


int main() {
	char ary[] = "1234567890";

	std::cout << "Before : " << ary << std::endl;

	std::memmove(ary, ary + 7, 3);

	std::cout << "After  : " << ary << std::endl;

	return 0;
}

