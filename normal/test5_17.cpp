#include <iostream>
#include <boost/utility.hpp>
#include <boost/type_traits/is_class.hpp>
#include <typeinfo>


// Use enable_if at default template parameter as a pointer constant.
// It's doesn't need to set dummy parameter.
// This method has 2 merit.
// 1. There isn't really possible that user specified value of dummy parameter.
// 2. This method can be applied to the function that fixed parameter numbers
//    like operators. 

// Why does enable_if declare as pointer constant?
// It can be declared as default template parameter.
/*
template <class T,
			class = typename boost::enable_if<boost::is_class<T>>::type>
void check(T value) { cout << "T is a class." << endl; }

template <class T,
			class = typename boost::disable_if<boost::is_class<T>>::type>
void check(T value) { cout << "T isn't a class." << endl; }

@ Let's see the signature of above functions.

template <class T, class U>
void check(T);

template <class T, class U>
void check(T);

These functions differ template default parameter type.
But the signature is same, and number of parameters are same
so these functions cannot be overloaded.


On the other hand, following code can be compiled.

using namespace boost;

template <class T,
			typename enable_if<is_class<T>>::type* = nullptr>
void check(T);

template <class T,
			typename disable_if<is_class<T>>::type* = nullptr>
void check(T);


					instanciation
enable_if<T>::type  => void
disable_if<T>::type => void

Judge that the function can be overloaded or not
will be done when function definition.


So if the function signature differ before instanciation,
they can be overloaded.


Above code cause compile error.
Because above 2 function are same signature,
it violates function overload condition.






*/


template <class T,
			typename boost::enable_if<boost::is_class<T>>::type* = nullptr>
void check(T value) {
	std::cout
		<< typeid(decltype(std::declval<T>())).name() << " is a class!\n";
}


template <class T,
			typename boost::disable_if<boost::is_class<T>>::type* = nullptr>
void check(T value) {
	std::cout
		<< typeid(decltype(std::declval<T>())).name() << " isn't a class!\n";
}

struct X {};


auto main() -> int {
	check(X());
	check(3);

	return 0;
}

