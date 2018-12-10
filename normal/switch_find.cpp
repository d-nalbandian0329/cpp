#include <iostream>
#include <type_traits>

struct has_find_member_impl {
	template <class T>
	static auto check(T*)
		-> decltype(
			std::declval<T>(),
			std::true_type()
		);

	template <class T>
	static auto check(...) -> std::false_type;
};

template <class T>
struct has_find_member
	: public decltype(has_find_member_impl::check<T>(nullptr)){};

template <class HasFind, class Key,
	typename std::enable_if<
		has_find_member<HasFind>::value
	>::type* = nullptr
>
auto find(const HasFind& obj, const Key& key)
	-> decltype(obj.find(key)){
	std::cout << "find() is member function." << std::endl;

	return obj.find(key);
}


template <class Container, class Key,
	typename std::enable_if<
		!has_find_member<Container>::value
	>::type* = nullptr
>
auto find(const Container& container, const Key& key)
	-> decltype(std::begin(container)) {

	std::cout << "find() is defined by user." << std::endl;

	auto first = std::begin(container);
	auto last  = std::end(container);

	while(first != last) {
		if(*first == key)
			break;
		++first;
	}

	return first;
}


#include <map>
#include <string>
#include <vector>

auto main() -> int {
	using namespace std;

	map<string, int> mp;

	mp["A"] = 10;
	mp["B"] = 20;
	mp["C"] = 30;
	mp["D"] = 40;

	auto ret = find(mp, "C");
}

