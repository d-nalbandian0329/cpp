// Judge whether the variadic templates
// contains specified type or not.

#include <iostream>
#include <typeinfo>


template <template<class> class Pred, class Head, class... Tail>
struct any_of {
	static const bool value
		= Pred<Head>::value ? true : any_of<Pred,Tail...>::value;
};

template <template<class> class Pred, class Head>
struct any_of<Pred, Head> {
	static const bool value = Pred<Head>::value;
};


template <class T>
struct is_int {
	static const bool value = false;
};


template <>
struct is_int<int> {
	static const bool value = true;
};



// trailing return type syntax
auto main() -> int {
	const bool result
		= any_of<is_int, char, long, double, int, float>::value;
	std::cout << (result ? "true" : "false") << std::endl;

	const bool result2
		= any_of<is_int, char, long, double, float>::value;
	std::cout << (result2 ? "true" : "false") << std::endl;

	return 0;
}

