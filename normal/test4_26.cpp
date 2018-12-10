// Metafunction that add * N times to template parameter.
// This function use recursion for loop execution.

#include <iostream>
#include <typeinfo>


template <int N, class T>
struct add_pointer {
	typedef typename add_pointer<N-1, T>::type* type;
};

// This function is terminal of recursive call.
template <class T>
struct add_pointer<0,T> {
	typedef T type;
};


auto main() -> int {
	add_pointer<3,int>::type v;
	std::cout << "int*** : " << typeid(v).name() << std::endl;


	return 0;
}

