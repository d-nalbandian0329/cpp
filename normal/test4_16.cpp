#include <iostream>
#include <typeinfo>

// Declaration if_ meta-function.
// @Para1 : Condition at compile.
// @Para2 : Return this when Cond is true.
// @Para3 : Return this when Cond is false. 
template <bool Cond, class Then, class Else>
struct if_;

// Partial specialization.

// If Cond is true, this function called.
template <class Then, class Else>
struct if_<true, Then, Else> {
	typedef Then type;
};

template <class Then, class Else>
struct if_<false, Then, Else> {
	typedef Else type;
};


auto main() -> int {
	if_<true, int, double>::type  n1 {};
	if_<false, int, double>::type n2 {};

	std::cout << "true  : " << typeid(n1).name() << std::endl;
	std::cout << "false : " << typeid(n2).name() << std::endl;

	return 0;
}

