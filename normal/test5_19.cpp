// Switch sort implementation.

#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>
#include <list>
#include <algorithm>


struct has_sort_member_impl {
	template <class T>
	static auto check(T*)
		-> decltype(
			std::declval<T>().sort(), std::true_type()
		);

	template <class T>
	static auto check(...) -> std::false_type;
};

template <class T>
struct has_sort_member
	: public decltype(has_sort_member_impl::check<T>(nullptr)) {
};



template <class Sortable,
			typename std::enable_if<has_sort_member<Sortable>::value>::type* = nullptr>
void sort(Sortable& x) {
	x.sort();
}

template <class Range,
			typename std::enable_if<!has_sort_member<Range>::value>::type* = nullptr>
void sort(Range& x) {
	std::sort(std::begin(x), std::end(x));
}


// trailing return type syntax.
auto main() -> int {
	using namespace std;

	vector<int> v  {3,1,4};
	list<int>   ls {3,1,4};

	sort(v);
	sort(ls);

	cout << "vector :";
	for(int x : v)
		cout << " " << x;
	cout << endl;

	cout << "list   :";
	for(int x : ls)
		cout << " " << x;
	cout << endl;

	return 0;
}

