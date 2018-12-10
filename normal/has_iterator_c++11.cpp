#include <iostream>
#include <type_traits>

// 実装部分
struct has_iterator_impl_ {
	template <class U>
	static std::true_type check(typename U::iterator*);

	template <class U>
	static std::false_type check(...);
};

// std::true_type, std::false_typeは
// クラス内部に static constexpr bool value
// を持っていてその値はそれぞれtrue, false


// check 関数が返す型から派生させる
template <class T>
class has_iterator_
	: public decltype(has_iterator_impl_::check<T>(nullptr)){};


#include <vector>
#include <list>

// trailing return type syntax.
auto main() -> int {

	std::cout << std::boolalpha;
	std::cout << "vector<int> : " << has_iterator_<std::vector<int>>::value << std::endl;
	std::cout << "list<int>   : " << has_iterator_<std::list<int>>::value << std::endl;
	std::cout << "int[]       : " << has_iterator_<int []>::value << std::endl;

	return 0;
}

