#include <iostream>
#include <utility>
#include <boost/utility/enable_if.hpp>

struct has_add_member_impl {
	template <class T, class U>
	static auto check(T*, U*)
		-> decltype(
			std::declval<T>().add(std::declval<U>()),
			std::true_type()
		);

	template <class T, class U>
	static auto check(...) -> std::false_type;
};


template <class T, class U>
struct has_add_member
	: public decltype(
				has_add_member_impl::check<T,U>(nullptr,nullptr)
			) {};

// operator+ function template
// Only when T has add member function, this function will be called.

template <class T, class U>
typename boost::enable_if<has_add_member<T,U>, T>::type
	operator+(const T& a, const U& b) {

	return a.add(b);
}


class X {
	int value_;

public:
	X(int value) : value_(value) {}

	X add(const X& x) const {
		return (value_ + x.getValue());
	}

	int getValue() const {
		return value_;
	}
};


int main() {
	X a(1);
	X b(2);

	X r = a + b;

	std::cout << r.getValue() << std::endl;

	return 0;
}

