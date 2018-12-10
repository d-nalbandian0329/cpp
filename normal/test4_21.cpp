#include <iostream>
#include <typeinfo>


// This metafunction take constant as first parameter.
template <bool Cond, class Then, class Else>
struct if_c;

template <class Then, class Else>
struct if_c<true, Then, Else> {
	typedef Then type;
};

template <class Then, class Else>
struct if_c<false, Then, Else> {
	typedef Else type;
};


// Higher-order metafunction.
template <class Cond, class Then, class Else>
struct if_ : public if_c<Cond::value, Then, Else> {
};


template <int N>
struct is_even {
	static const bool value = N%2==0;
};


auto main() -> int {
	if_<is_even<2>, float, uint64_t>::type n1 {};
	if_<is_even<1>, float, uint64_t>::type n2 {};

	std::cout << "true  : " << typeid(n1).name() << std::endl;
	std::cout << "false : " << typeid(n2).name() << std::endl;

	return 0;
}

