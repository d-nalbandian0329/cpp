// Substitution Failure Is Not An Error.


#include <iostream>
#include <type_traits>
#include <utility>
#include <typeinfo>



template <int N>
struct int_ {};


template <class T, int N,
	typename std::enable_if<(N > 0)>::type* = nullptr>
auto add_pointer(T, int_<N>)
	-> decltype(add_pointer(std::declval<T*>(), int_<N-1>()));

template <class T, int N,
	typename std::enable_if<(N==0)>::type* = nullptr>
auto add_pointer(T, int_<N>)
	-> T;

// trailing return type syntax.
auto main() -> int {
	typedef decltype(add_pointer(std::declval<int>(), int_<4>()))
		ret_4;
	typedef decltype(add_pointer(std::declval<int>(), int_<6>()))
		ret_6;

	ret_4 n1;
	ret_6 n2;

	std::cout << "ret_4 : " << typeid(n1).name() << std::endl;
	std::cout << "ret_6 : " << typeid(n2).name() << std::endl;

	return 0;
}

