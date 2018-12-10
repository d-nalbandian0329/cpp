#include <iostream>
#include <typeinfo>


template <class T>
T* add_pointer_();


template <class T>
struct add_pointer {
	typedef T* type;
};


auto main() -> int {
	typedef decltype(add_pointer_<int>()) result;
	result n;

	add_pointer<int>::type x;

	add_pointer<add_pointer<int>::type>::type ipp;

	std::cout << typeid(n).name() << std::endl;
	std::cout << typeid(x).name() << std::endl;
	std::cout << typeid(ipp).name() << std::endl;

	return 0;
}

