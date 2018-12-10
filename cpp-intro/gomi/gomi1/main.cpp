#include <iostream>
#include "sample.h"

auto main() -> int {
	Sample obj {};

	std::cout << obj.get() << std::endl;

	obj.set(100);

	std::cout << obj.get() << std::endl;
}

