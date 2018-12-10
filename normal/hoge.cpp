// C++11版

#include <iostream>
#include <utility>
#include <typeinfo>
#include <type_traits>



// wrapper class
template <int N>  struct int_  {};
template <bool N> struct bool_ {};

// tag structure
struct cont {};
struct end  {};


// Check end flag.
// If parameter is true, return end tag.
// std::conditional equal to if_c metafunction.
// この引数って使わないのになんで受け取らないかんのかな？？
// 結局, 戻り値にCondそのまま渡してんでから
template <bool Cond>
auto is_end(bool_<Cond>)
	-> typename std::conditional<Cond,end,cont>::type;


// recursive template
// This function called when N != 0.
template <class T, int N>
auto add_pointers_impl(T, int_<N>, cont)
	-> decltype(
		add_pointers_impl(
			std::declval<T*>(),
			int_<N-1>(),
			std::declval<decltype(is_end(bool_<N-1==0>()))>()
		)
	);


// 呼び出し終端での処理
template <class T, int N>
auto add_pointers_impl(T, int_<N>, end)
	-> T;

template <class T, int N>
auto add_pointers(T, int_<N>)
	-> decltype(
		add_pointers_impl(
			std::declval<T>(),
			int_<N>(),
			std::declval<decltype(is_end(bool_<N==0>()))>()
		)
	);


auto main() -> int {
	typedef decltype(add_pointers(std::declval<double>(), int_<3>()))
		dp3;

	dp3 n;

	std::cout << typeid(dp3).name() << std::endl;

	return 0;
}

