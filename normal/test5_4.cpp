#include <iostream>

template <class T>
struct is_pointer_ {
	static const bool value = false;
};

// partial specialization
template <class T>
struct is_pointer_<T*> {
	static const bool value = true;
};

auto main() -> int {
	std::cout << std::boolalpha;

	std::cout << is_pointer_<void>::value << std::endl;
	std::cout << is_pointer_<int>::value << std::endl;
	std::cout << is_pointer_<char*>::value << std::endl;

	return 0;
}

