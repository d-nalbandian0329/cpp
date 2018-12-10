#include <iostream>
#include <typeinfo>

// Identity meta-function.
template <class T>
struct remove_const {
	typedef T type;
};

// Partial specialization for remove const modifier
// from type const T.
template <class T>
struct remove_const<const T> {
	typedef T type;
};


template <class T>
struct remove_volatile {
	typedef T type;
};

// This meta-function removes volatile modifier.
template <class T>
struct remove_volatile<volatile T> {
	typedef T type;
};


// The typename keyword specify that follow name
// denpends on template parameter.
template <class T>
struct remove_cv {
	typedef
		typename remove_const<
			typename remove_volatile<T>::type
		>::type
	type;
};


auto main() -> int {
	remove_cv<const volatile int>::type value = 5;
	std::cout << value << " : ";
	value = 1;
	std::cout << value << std::endl;
	return 0;
}

