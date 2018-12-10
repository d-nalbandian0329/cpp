// Check the class is assignable or not.

#include <iostream>
#include <type_traits>

struct is_assignable_impl {
	// T is assignable.
	template <class T>
	static auto check(T*) -> decltype(
		std::declval<T&>() = std::declval<const T&>(),
		std::true_type()
	);

	// T isn't assignable.
	template <class T>
	static auto check(...) -> std::false_type;
};


template <class T>
class is_assignable_
	: public decltype(is_assignable_impl::check<T>(nullptr)) {};


struct X {
	X& operator=(const X&) = delete;
};

struct Y {};


// trailing return type syntax.
auto main() -> int {
//	Compile error occurs.
//	static_assert(is_assignable_<X>::value, "X isn't assignable class.");

	static_assert(is_assignable_<Y>::value, "Y isn't assignable class.");
}

