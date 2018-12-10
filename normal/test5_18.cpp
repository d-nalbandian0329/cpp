// Overloading that contingent on having
// specialized implementation.

// Standard Library has std::sort() that
// sort elements in container with speciied range.
// Since std::sort() requires random access iterator,
// it can't apply to std::list.

// has_sort_member
// judge that whether T has std::sort() member or not.

#include <iostream>
#include <type_traits>
#include <utility>

struct has_sort_member_impl {
	template <class T>
	static auto check(T*)
		-> decltype(std::declval<T>().sort(),std::true_type());

	template <class T>
	static auto check(...) -> std::false_type;
};


template <class T>
struct has_sort_member
	: public decltype(has_sort_member_impl::check<T>(nullptr)) {};


#include <vector>
#include <list>

auto main() -> int {
	std::cout << has_sort_member<std::vector<int>>::value << std::endl;
	std::cout << has_sort_member<std::list<int>>::value << std::endl;
}

