#include <iostream>
#include <string>
#include "twostrings.h"

void test() {
	TwoStrings obj;

	obj.setPreString("Hello");
	obj.setPostString(",world!");

	std::cout << obj.getConnectedString() << std::endl;
	std::cout << obj.getConnectedLength() << std::endl;
}


auto main() -> int {
	test();
}

