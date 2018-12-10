#include <iostream>
#include <algorithm>
#include <iterator>
#include <type_traits>

struct has_sort_member_impl {
	template <class T>
	static auto check(T*) -> decltype(
		std::declval<T>().sort(),
		std::true_type()
	);

	template <class T>
	static auto check(...) -> std::false_type;
};

// High-order metafunction
template <class T>
struct has_sort_member
	: public decltype(has_sort_member_impl::check<T>(nullptr)){};


template <class Sortable,
	typename std::enable_if<
		has_sort_member<Sortable>::value
	>::type* = nullptr>
void sort(Sortable& obj) {
	std::cout << "Inherent Sort Function." << std::endl;
	obj.sort();
}


template <class Range,
	typename std::enable_if<
		!has_sort_member<Range>::value
	>::type* = nullptr>
void sort(Range& obj) {
	std::cout << "General Sort Function." << std::endl;
	std::sort(std::begin(obj), std::end(obj));
}


#include <list>
#include <vector>

auto main() -> int {
	using namespace std;

	vector<int> iv {3,1,4};
	list<int>	li {3,1,4};

	sort(iv);
	sort(li);
}




