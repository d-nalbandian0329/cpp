// 型T特定の型を持っているか否かを判定する関数
#include <iostream>
#include <vector>

template <class T>
constexpr bool has_iterator_impl(typename T::iterator*) {
	return true;
}

template <class T>
constexpr bool has_iterator_impl(...) {
	return false;
}

template <class T>
constexpr bool has_iterator() {
	return has_iterator_impl<T>(nullptr);
}



// trailing return type syntax.
auto main() -> int {
	static_assert(
		!has_iterator<std::vector<int>>(),
		"std::vector<int> doesn't have iterator.\n"
	);

	static_assert(
		!has_iterator<int>(),
		"int doesn't have iterator.\n"
	);

	return 0;
}

