#include <iostream>
#include <utility>
#include <type_traits>
#include <typeinfo>


// Express static value of each type.
template <int N>
struct int_ {};

template <bool B>
struct bool_ {};


// These tag express recursive state.
struct cont {};  // continue
struct end  {};  // finish


// std::conditional is equal to if_c.
// If first paramter is true, return second parameter as type member.
template <bool Cond>
auto is_end(bool_<Cond>)
	-> typename std::conditional<Cond, end, cont>::type;

// Recursive template.
template <class T, int N>
auto add_pointers_impl(T, int_<N>, cont)
	-> decltype(
		add_pointers_impl(
			std::declval<T*>(),
			int_<N-1>(),
			std::declval<decltype(is_end(bool_<N-1==0>()))>()
		)
	);


template <class T, int N>
auto add_pointers_impl(T, int_<N>, end) -> T;



template <class T, int N>
auto add_pointers(T, int_<N>)
	-> decltype(
		add_pointers_impl(
			std::declval<T>(),
			int_<N>(),
			std::declval<decltype(is_end(bool_<N==0>()))>()
		)
	);


auto main() -> int {
	// Execute metafunction.
	typedef
		decltype(add_pointers(std::declval<int>(), int_<3>()))
	result_3;

	result_3 n;

	std::cout << "int*** : " << typeid(n).name() << std::endl;

	return 0;
}

// Before C++03, condition blanch is expressed by specialization
// of class template. In C++11, overloading function template
// can express condition blanch.

/*
// This expression mean that add three * to int.
typedef
	decltype(add_pointers(std::declval<int>(), int_<3>()))
	result;

std::declval  =>  Get type value.

int_ => class template show that the value is static.

// This class template receive int value that compile time constant.
// This function used for receiving static value as parameter.
template <int N>
struct int_ {};

// trailing return type syntax.
// This function call implimented function at return type position.

// At first, user calls this function.
// Blanching process by Tag Dispatch.
template <class T, int N>
auto add_pointers(T, int_<N>)
	-> decltype(
		add_pointers_impl(
			std::declval<T>(),
			int_<N>(),			
			std::declval<decltype(is_end(bool_<N==0>()))>()
		)
	);

// continue tag
struct cont {};

// end tag
struct end  {};

// This metafunction returns tag.
template <bool Cond>
auto is_end(bool_<Cond>)
 	-> typename std::conditional<Cond, end, cont>::type;

// recursive template
// If third parameter is cont tag, this function will be called.
template <class T, int N>
auto add_pointers_impl(T, int_<N>, cont)
	-> decltype(
		add_pointers_impl(
			std::declval<T*>(),
			int_<N-1>(),
			std::declval<decltype(is_end(bool_<N-1==0>()))>()
		)
	);

// When third parameter is end tag, this function will be called.
template <class T, int N>
auto add_pointers_impl(T, int_<N>, end)
	-> T;

*/


