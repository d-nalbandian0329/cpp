/*
since C++11

std::declval

@Defined in header <utility>
template <class T>
typename std::add_rvalue_reference<T>::type declval() noexcept;


Converts any type T to a reference type,
making it possible to use member functions
in decltype expressions without the need to go through
constructors.

declval is commonly used in templates where acceptable
template parameters may have no constructor in common,
but have the same member function whose return type is needed.

Note that because no definition exists for decval,
it can only be used in unevaluated contexts;
it is an error to evaluate an expression that contains this function.

Formally, the program is ill-formed if this function is odr-used.

@Parameter:(none)

@Return type
Cannot be called and thus never returns a value.
The return type is T&& unless T is (possibly cv-qualified) void,
in which case the return type is T.
*/

#include <iostream>
#include <utility>

struct Default { int foo() const { return 1; } };

struct NonDefault {
	NonDefault(const NonDefault&){}
	int foo() const {return 1;}
};


int main() {
	// type of n1 is int.
	decltype(Default.foo()) n1 = 1;

	// error : no default constructor
	// decltype(NonDefault().foo()) n2 = n1;

	// type of n2 is int.
	decltype(std::declval<NonDefault>().foo()) n2 = n1;

	std::cout << "n1 = " << n1 << std::endl;
	std::cout << "n2 = " << n2 << std::endl;

	return 0;
}

