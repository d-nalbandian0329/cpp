// T型に指定数の関節参照演算子を加えるメタ関数

#include <iostream>
#include <typeinfo>

// Wrapper class.
template <int N>  struct int_ {};
template <bool B> struct bool_{};

// tag structure for tag dispatch.
struct cont {};
struct end  {};

// 継続・終了判定メタ関数
template <bool Cond>
auto is_end(bool_<Cond>)
	-> typename std::conditional<Cond, end, cont>::type;


// add_pointers_impl は名前空間修飾できない



// 処理部分, 通常時
template <class T, int N>
auto add_pointers_impl(T, int_<N>, cont)
	-> decltype(
		add_pointers_impl(
			std::declval<T*>(),
			int_<N-1>(),
			std::declval<decltype(is_end(bool_<N-1==0>()))>()
		)
	);

// 終了時処理
template <class T, int N>
auto add_pointers_impl(T, int_<N>, end)
	-> T;


// インターフェース
// trailing return type syntax.

template <class T, int N>
auto add_pointers(T, int_<N>)
	-> decltype(
		add_pointers_impl(
			std::declval<T>(),
			int_<N>(),
			// Tag dispatch.
			std::declval<decltype(is_end(bool_<N==0>()))>()
		)
	);


auto main() -> int {
	// メタ関数の呼び出し
	typedef
		decltype(add_pointers(std::declval<int>(), int_<4>()))
	ip4;

	ip4 n;

	std::cout << typeid(n).name() << std::endl;

	return 0;
}

