// 対象の型がイテレータを持っているかどうか
// 判定する関数
#include <iostream>

// 持っている場合
template <class T>
constexpr bool has_iterator_impl(typename T::iterator*) {
	return true;
}

// こいつの引数がいまいちわからん
// ... ってパラメータパックのものと同じ？
template <class T>
constexpr bool has_iterator_impl(...) {
	return false;
}

template <class T>
constexpr bool has_iterator() {
	return has_iterator_impl<T>(nullptr);
}


#include <vector>
#include <list>

auto main() -> int {
	std::vector<int> iv;
	std::list<int> 	 il;
	int ia[10];

	std::cout << std::boolalpha;
	std::cout << "vector<int> : " << has_iterator<std::vector<int>>() << std::endl;
	std::cout << "list<int>   : " << has_iterator<std::list<int>>() << std::endl;
	std::cout << "int[]       : " << has_iterator<decltype(ia)>() << std::endl;

}




