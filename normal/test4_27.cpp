// Variadic templates is considered as type list.
// Because it has function that treat any number of any type object. 

// Basic operator of type list
// Decomposition list to set header and others.

#include <iostream>
#include <tuple>
#include <typeinfo>

template <class Head, class... Tail>
struct g {
	typedef Head head;

	// Use tuple because multiple type cannot be operand of typedef.
	typedef std::tuple<Tail...> tail;
};


template <class... List>
struct f {
	typedef typename g<List...>::head head;
	typedef typename g<List...>::tail tail;
};


// trailing return type syntax.
auto main() -> int {
	typedef f<int,char,long,double> list;

	std::cout << typeid(list::head).name() << std::endl;
	std::cout << typeid(list::tail).name() << std::endl;

	return 0;
}

