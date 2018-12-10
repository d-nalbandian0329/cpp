#include <iostream>
#include <typeinfo>


// Judge that parameter is even or not.
template <int N>
struct is_even {
	static const bool value = N%2==0;
};


// This metafunction receive tempalte parameters
// that used compile condition.
// This metafunction never called, so you need not
// to define this.
template <bool Cond, class Then, class Else>
struct if_c;


// Partial specialization.
template <class Then, class Else>
struct if_c <true, Then, Else>{
	typedef Then type;
};

//
template <class Then, class Else>
struct if_c<false, Then, Else> {
	typedef Else type;
};

// Higher-order metafunction.
// This function receive if_c function.
// This funcion must be defined.
template <class Cond, class Then, class Else>
struct if_ : public if_c<Cond::value, Then, Else> {};



auto main() -> int {
	if_c<true, int, double>::type  n1 {};
	if_c<false, int, double>::type n2 {};

	if_<is_even<1>, int, double>::type n3 {};
	if_<is_even<2>, int, double>::type n4 {};

	std::cout << "true  : " << typeid(n1).name() << std::endl;
	std::cout << "false : " << typeid(n2).name() << std::endl;

	std::cout << "Even : " << typeid(n3).name() << std::endl;
	std::cout << "Odd  : " << typeid(n4).name() << std::endl;

	return 0;
}

