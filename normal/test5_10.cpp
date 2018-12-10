#include <iostream>
#include <type_traits>


// Implementation of is_assignable metafunction.
struct is_assignable_impl_ {
	// Why parameter of this function is a pointer to T?
	// 
	template <class T>
	static auto check(T*)
		-> decltype(
			// 後置したdecltypeのところでSFINAEが働く
			// 下の記述は代入が可能かどうかを判別する
			// 型Tがa = bという式で代入可能か
			// インスタンス化の結果代入式が置き換えに失敗すると
			// オーバーロード解決の結果2番目のcheck()関数が適合する
			// この関数では2番目の関数と対応させるために
			// comma演算子で戻り値をstd::true_typeにしている
			std::declval<T&>() = std::declval<const T&>(),
			std::true_type()
		);

	template <class T>
	static auto check(...) -> std::false_type;
};


template <class T>
class is_assignable_
	: public decltype(is_assignable_impl_::check<T>(nullptr)) {};


// Test class doesn't have assignment operator.
class Test {
	Test& operator=(const Test&) = delete;
};

class B {};


auto main() -> int {
	std::cout << std::boolalpha;
	std::cout << "Test : " << is_assignable_<Test>::value << std::endl;
	std::cout << "B    : " << is_assignable_<B>::value << std::endl;

	return 0;
}

