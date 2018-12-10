#include <iostream>
#include <typeinfo>

// Identity meta-function.
template <class T>
struct identity {
	typedef T type;
};

// Add pointer meta-function.
template <class T>
struct add_pointer {
	typedef T* type;
};


int main() {
	std::cout << typeid(identity<int>::type).name() << std::endl;

	int value = 3;
	add_pointer<int>::type p = &value;
	add_pointer<add_pointer<int>::type>::type pp = &p;

	std::cout << value << std::endl;
	std::cout << *p << std::endl;
	std::cout << **pp << std::endl;

	return 0;
}

