#include <iostream>
#include <typeinfo>

// 
template <class T>
struct add_const {
	typedef const T type;
};

template <class T>
struct add_lvalue_reference {
	typedef T& type;
};

// Avoid adding lvalue reference to lvalue reference,
// define partial specialization.
template <class T>
struct add_lvalue_reference<T&> {
	typedef T& type;
};


// Combine add_const with add_lvalue_reference.
template <class T>
struct add_const_lvalue_reference {
	typedef typename add_const<typename add_lvalue_reference<T>::type>::type type;
};

auto main() -> int {
	int value = 3;

	add_const<decltype(value)>::type c = value;

	add_lvalue_reference<add_const<decltype(value)>::type>::type lrc = value;

	add_const<add_lvalue_reference<decltype(value)>::type>::type clr = value;

	add_const_lvalue_reference<int>::type clr2 = value;

	std::cout << typeid(c).name() << std::endl;
	std::cout << typeid(lrc).name() << std::endl;
	std::cout << typeid(clr).name() << std::endl;
	std::cout << typeid(clr2).name() << std::endl;

	return 0;
}

