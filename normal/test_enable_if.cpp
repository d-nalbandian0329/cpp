// Practice to use Boost enable_if metafunction.
// This function call arbitrary overloaded function with SFINAE.
#include <iostream>
#include <boost/utility.hpp>


// If template parameter is class, check1 will be called.
// And not, check2 will be called.

// boost::enable_if
// This metafunction is high-ordered metafunction.
// So, this receives metafunction used to judge that it's able to be overloaded or not.
// If it's be able to be overloaded, this returns true.
// 受け取ったメタ関数が真を返した時のみオーバーロードの候補になる

// If enable_if receive false at first parameter,
// type member isn't defined.

// So this template function is out from overload candidate.

// 1
template <class T>
void check(T value,
			typename boost::enable_if<boost::is_class<T>>::type* = nullptr) {
	std::cout << "T is class.\n";
}

// 2
template <class T>
void check(T value,
			typename boost::disable_if<boost::is_class<T>>::type* = nullptr) {
	std::cout << "T isn't class.\n";
}

struct X {};

auto main() -> int {
	check(X());
	check(3);
}

