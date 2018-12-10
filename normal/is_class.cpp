// Metafunction recognize whether the template parameter is
// class or not.
#include <iostream>
#include <type_traits>


struct is_class_impl {
	template <class T>
	static auto check(int T::*) -> std::true_type;

	template <class T>
	static auto check(...) -> std::false_type;
};

template <class T>
class is_class_
	: public decltype(is_class_impl::check<T>(nullptr)) {};


struct X {};


auto main() -> int {
	static_assert(is_class_<X>::value, "X isn't a class");

//  Compile error occurs.
//	static_assert(is_class_<int>::value, "X isn't a class");
}

