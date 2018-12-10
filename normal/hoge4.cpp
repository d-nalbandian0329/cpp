#include <iostream>
#include <initializer_list>

class Foo {
private:
	int sum;

public:
	Foo(std::initializer_list<int> list) : sum(0) {
		for(auto ite = list.begin(); ite != list.end(); ++ite)
			sum += *ite;
	}
};


auto main() -> int {
	{
		Foo foo0({});
		Foo foo1({1});
		Foo foo2({1,2});
		Foo foo3({1,2,3});
	}

	{
		Foo foo0 = { };
		Foo foo1 = {1};
		Foo foo2 = {1,2};
		Foo foo3 = {1,2,3};
	}

	{
		// コンストラクタの呼び出しに()の代わりに{}を使える
		// C++0xより
		Foo foo0 { };
		Foo foo1 {1};
		Foo foo2 {1,2};
		Foo foo3 {1,2,3};
	}

	return 0;
}


/*
クラスの初期化に () を使うと関数のプロトタイプ宣言
と曖昧になってしまうので

// 引数を取らずFoo型の戻り値を返すwrongという名前の
// 関数のプロトタイプ宣言
Foo wrong();

// Foo型のokeyという名前の変数の宣言
Foo okey {};

代入でもリスト初期化を使えるがその場合は
別に代入演算子も定義しないといけない


*/

