#include <iostream>
#include <typeinfo>
#include <tuple>


template <template<class> class Pred, class List>
struct any_of_impl;

template <template <class> class Pred, class Head, class... Tail>
struct any_of_impl<Pred, std::tuple<Head, Tail...>> {
	static const bool value =
		Pred<Head>::value ? true
			: any_of_impl<Pred, std::tuple<Tail...>>::value;
};


// Partial specialization.
template <template <class> class Pred>
struct any_of_impl<Pred, std::tuple<>> {
	static const bool value = false;
};



template <template <class> class Pred, class... List>
struct any_of {
	static const bool value =
		any_of_impl<Pred, std::tuple<List...>>::value;
};


// A metafunction check that template parameter is integer type.
template <class T>
struct is_int {
	static const bool value = false;
};

template <>
struct is_int<int> {
	static const bool value = true;
};


// trailing return type syntax.
auto main() -> int {
	const bool ret = any_of<is_int, char, long, double, int, float>::value;
	const bool ret2 = any_of<is_int, char, long, double, uint64_t, float>::value;

	std::cout << (ret ? "true" : "false") << std::endl;
	std::cout << (ret2 ? "true" : "false") << std::endl;

	return 0;
}

