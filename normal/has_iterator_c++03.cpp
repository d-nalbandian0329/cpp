// C++03ではconstexprがないのでその代わりとして
// sizeof演算子を用いていた

#include <iostream>

template <class T>
class has_iterator {
	// constexprがないので代わりに別名を与えた構造体を返すようにして
	// そのサイズをsizeof演算子で取得して結果に利用する
	typedef char yes;
	typedef struct {char a[2];} no;

	// この関数は定義しない
	template <class U>
	static yes check(typename U::iterator*);

	//
	template <class U>
	static no check(...);


public:
	// 戻り値のサイズがyesのサイズと一致するかどうか
	static const bool value = sizeof(check<T>(0)) == sizeof(yes);
};


/*
sizeof演算子に関数適用の結果を渡すとその関数は実際に呼び出されず
戻り値の値の型のサイズが返る
*/


#include <vector>

int main() {
	std::cout << has_iterator< std::vector<int> >::value << std::endl;
	std::cout << has_iterator<int []>::value << std::endl;

	return 0;
}

