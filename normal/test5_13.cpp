// Example for Boost enable_if metafunction.
#include <iostream>
#include <boost/utility.hpp>

template <class T>
void check(T value,
			typename boost::enable_if<boost::is_class<T>>::type* = nullptr){
	std::cout << "T is a class." << std::endl;
}

template <class T>
void check(T value,
			typename boost::disable_if<boost::is_class<T>>::type* = nullptr){
	std::cout << "T isn't a class." << std::endl;
}


struct X {};

// trailing return type synax.
auto main() -> int {
	std::cout << std::boolalpha;

	std::cout << "int : "; check(3);
	std::cout << "X   : "; check(X());

	return 0;
}

