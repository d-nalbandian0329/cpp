#include <iostream>
#include <utility>
#include <typeinfo>


// C++03 style metafunctoin that add pointer to
// template patameter.
template <class T>
struct add_pointer_03 {
	typedef T* type;
};


// C++ 11 style metafunction.
// Avoid misscalling, this function must not to be defined.
template <class T>
T* add_pointer_11();


// declval
// header : <utility>
// declval has no implementation.
// This function has no parameter, and return rvalue reference of
// template paramter T.
// Function call of declval only allowed in context of decltype.
/*
namespace std {
	template <class T>
	typename add_rvalue_reference<T>::type
	declval() noexcept;
}
*/

// Improve expression of metafunction.
template <class T>
T* add_pointer_(T);

auto main() -> int {
	add_pointer_03<int>::type n1 {};

	// Paramter of deltype never evaluate,
	// so it's need only function signature.
	decltype(add_pointer_11<int>()) n2;

	std::cout << "03 : " << typeid(n1).name() << std::endl;
	std::cout << "11 : " << typeid(n2).name() << std::endl;

	#define DECLVAL(x) std::declval<x>()

	// Execute metafunction.
	decltype(add_pointer_(DECLVAL(int))) result;

	std::cout << "new : " << typeid(result).name() << std::endl;
	
	return 0;
}

