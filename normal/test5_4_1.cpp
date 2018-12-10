// type traits metafunction in C++03

#include <iostream>

// 変更点：戻り値としてbool値を返すのではなく
//         iterator型を持っていればyes型
//         持っていなければの型を返す

template <class T>
class has_iterator {
	typedef char yes;
	typedef struct { char a[2]; } no;

	template <class U>
	static yes test(typename U::iterator*);

	template <class U>
	static no test(...);

public:
	// sizeofの引数に関数適用の結果を渡した場合, その関数は
	// 実際には呼び出されず戻り値の型のサイズが帰る
	static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};


