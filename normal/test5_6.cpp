// 指定されたテンプレートパラメータがクラスかどうか判定する
// What is class feature?
// * Using syntax that allowed only class.
// * Can define member.
// So if template parameter T is class, T has a pointer to member "int T::*".

#include <iostream>
#include <type_traits>


// This class has two member method declaration.
// These method need not to be defined.
// Because User only use return type of these function with decltype.
struct is_class_impl_ {
	// Should I write typename here?

	// ここでは引数の型にint型メンバへのポインタをとっている
	// そのためint型のメンバを持つクラスのみが対象となるように見える
	// しかし, 実際には空のクラスであってもこちらの関数の対象となる
	// これは int T::* がテンプレートの置き換えにのみ使われるためである
	// そのためメンバ変数ポインタを持つことのできる、構造体とクラス
	// がテンプレートパラメータとして渡された時下の関数が呼び出される
	//template <class T>
	//static std::true_type check(int T::*);

	// Function parameter is a pointer to member function.
	template <class T>
	static std::true_type check(void (T::*)());

	template <class T>
	static std::false_type check(...);
};


template <class T>
class is_class_
	: public decltype(is_class_impl_::check<T>(nullptr)) {};


struct X {};

class Y {};


// trailing return type syntax.
auto main() -> int {
	std::cout << std::boolalpha;

	std::cout << "Structure : " << is_class_<X>::value << std::endl;
	std::cout << "Class     : " << is_class_<Y>::value << std::endl;
	std::cout << "int       : " << is_class_<int>::value << std::endl;

	return 0;
}

