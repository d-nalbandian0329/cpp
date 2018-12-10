#include <iostream>


// メタ関数, 実際の判定は内部の関数で行い
// 結果はフィールドのクラス定数の中に入れておく
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
	static constexpr bool value = check<T>(nullptr);
};


#include <vector>
#include <list>

auto main() -> int {
	std::cout << std::boolalpha;
	std::cout << "vector<int> : " << has_iterator<std::vector<int>>::value << std::endl;
	std::cout << "list<int>   : " << has_iterator<std::list<int>>::value << std::endl;
	std::cout << "int[]       : " << has_iterator<int []>::value << std::endl;

	return 0;
}

