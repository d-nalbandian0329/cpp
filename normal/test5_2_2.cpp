// 型Tが特定の型を持っているか判別する関数のメタ関数ver
// 関数のままでも問題ないが, 標準ライブラリやBoost
// ではこのような処理をメタ関数で記述している実績がある

#include <iostream>

template <class T>
class has_iterator {
	template <class U>
	static constexpr bool check(typename U::iterator*){
		return true;
	}

	// partial specialization
	template <class U>
	static constexpr bool check(...){
		return false;
	}

public:
	static const bool value = check<T>(nullptr);
};

#include <vector>

// trailing return type syntax
auto main() -> int {
//	static_assert(
//		has_iterator<int>::value,
//		"int doesn't have iterator."
//	);

	static_assert(
		has_iterator<std::vector<int>>::value,
		"std::vector<int> doesn't have iterator."	
	);
}

