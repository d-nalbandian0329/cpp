#include <iostream>
#include <utility>
#include <boost/utility/enable_if.hpp>


// Implementation of has_add_member
struct has_add_member_impl {
	// In decltype, if T doesn't have add member function,
	// this function removed from overload candidate.
	template <class T, class U>
	static auto check(T*, U*)
		-> decltype(
			std::declval<T>().add(std::declval<U>()),
			std::true_type()
		);

	// Other parameter pattern.
	template <class T, class U>
	static auto check(...) -> std::false_type;
};


// This metafunction judge whether T has add member function
// with U lvalue reference as parameter or not.
template <class T, class U>
class has_add_member
	: public decltype(has_add_member_impl::check<T,U>(nullptr,nullptr)){};


/*
Implemntation of boost::enable_if.

template <bool B, class T = void>
struct enable_if_c {
	typedef T type;
};

template <class T>
struct enable_if_c<false, T> {};

template <class Cond, class T = void>
struct enable_if
	: public enable_if_c<Cond::value,T> {};

So in following template function

if has_add_member<T,U> is true,
boost::enable_if<has_add_member<T,U>,T>::type
is replaced by T.

operator+ can be called only when T has add() member function.

Since the number of operator's parameter is fixed,
couldn't add enable_if as dummy parameter.

2nd template parameter of enable_if is void,
but specified type is T that is return type of operator+.

*/

template <class T, class U>
typename boost::enable_if<has_add_member<T,U>,T>::type
	operator+(const T& n1, const U& n2) {
	return n1.add(n2);
}

class X {
	int value_;

public:
	X(int value) : value_(value) {}

	X add(const X& r) const {
		return X(value_ + r.getValue());
	}

	int getValue() const { return value_; }
};


// trailing return type syntax.
auto main() -> int {
	X x1(10), x2(20);
	X ret = x1 + x2;
	std::cout << ret.getValue() << std::endl;

	return 0;
}

