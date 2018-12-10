#include <iostream>

template <class T>
struct add_lvalue_reference {
	typedef T& type;
};

template <class T>
struct add_lvalue_reference<T&> {
	typedef T& type;
};


// transform apply F to each element in type list.
template <template <class> class F, class... List>
struct transform {
	typedef std::tuple<typename F<List>::type...> type;
};

auto main() -> int {
	typedef
		transform<add_lvalue_reference, int, char, double>::type
	result;

	// result == tuple<int&, char&, double&>

	return 0;
}



// Boost MetaProgramming Library
// C++ template でどのくらいのアルゴリズムを記述できる？

// C++ Templates are Turing Complete

// Turing Complete
// Alan Mathieson Turingが考案したTuring Machineと同等の
// 機能を持つ言語は計算完備, つまりすべてのアルゴリズムを
// 解くことができる
// 上記の論文ではC++テンプレートはほぼチューリング完全であると記述されている

// C++では再帰テンプレートによってループを表現できるが
// ループの回数を無制限に許可するとコンパイルに無限の時間が
// かかってしまうので言語規格でテンプレートの再帰回数が制限されている

// 以上の理由からC++テンプレートは厳密にはTuring Completeではないが
// Turing Machineの要件はほぼ満たしており, 多くのアルゴリズムが解ける

// C++03では17回, C++11では1024回まで
// => コンパイラによっては再帰回数を指定できる
//    gccでは -ftemplate-depth-n のようにコンパイルオプションを設定する
//    ことでn回の再帰ができるようになる



