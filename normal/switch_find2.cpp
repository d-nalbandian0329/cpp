#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

template <class Container>
auto my_find(const Container& c, typename Container::key_type key)
	-> decltype((c.find(key))) {
	std::cout << "member" << std::endl;
	return (c.find(key));
}

template <class Container>
decltype(auto) my_find(const Container& c,
						typename Container::value_type v) {
	std::cout << "free" << std::endl;

	return (std::find(c.begin(), c.end(), v));
}


int main() {
	std::vector<int> a {1, 2, 3};
	std::map<int,int> b;

	b[0] = 1;
	b[2] = 3;
	b[4] = 5;

	auto&& iter1 = my_find(a, 2);
	std::cout << (iter1 == a.end() ? "not found" : "found")
		<< std::endl;

	auto&& iter2 = my_find(b, 2);
	std::cout << (iter2 == b.end() ? "not found" : "found")
		<< std::endl;

	return 0;
}

