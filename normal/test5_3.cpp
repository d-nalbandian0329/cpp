#include <iostream>

template <class T>
class has_iterator {
	template <class U>
	static constexpr bool check(typename U::iterator*) {
		return true;
	}

	template <class U>
	static constexpr bool check(...) {
		return false;
	}

public:
	static const bool value = check<T>(nullptr);
};


#include <vector>

auto main() -> int {
	std::cout << std::boolalpha;

	std::cout << has_iterator<std::vector<int>>::value << std::endl;

}

