// SFINAE(Substitution Failure Is Not An Error)
// テンプレートをインスタンス化する際に置き換え失敗
// を検知したらその関数をオーバーロードの候補から
// 外す作用のこと

#include <iostream>

using namespace std;

struct widget {
	typedef int value_type;
};


template <class T>
void dosomething(typename T::value_type*) {
	cout << "value_typeを持っている" << endl;
}

template <class T>
void dosomething(...) {
	cout << "value_typeを持ってない" << endl;
}

auto main() -> int {
	/*
	template <class T>
	void dosomething(typename T::value_type*)
	が呼び出される
	*/
	dosomething<widget>(0);

	/*
	template <class T>
	void dosomething(...)
	が呼び出される
	*/
	dosomething<int>(0);


	// つまりここでは型Tがvalue_typeを持っているか
	// どうかでオーバーロードできている

}


/*
ひとつ目のdosomething関数template
parameter : T::value_type*

instanciation
void dosomething_of_widget(widget::value_type*)

このようにテンプレートパラメータにvalue_type型の
定義されていwidget型を指定すると問題なくインスタンス化
される

一方int型をテンプレートパラメータとして渡した場合
void dosomething_of_int(int::value_type*)
のようなインスタンス化が試みられる

int型はvalue_typeという型を持っていないのでテンプレート
の置き換え失敗が発生する
=> SFINAE(Substitution Failure Is Not An Error)
   の発生

テンプレートの置き換えに失敗した場合に
エラーを発生させるのではなくその関数テンプレート
をオーバーロードの候補から外す

よってひとつ目のテンプレート関数のインスタンス化に
失敗したあと, それがオーバーロードの候補から外され
ふたつ目の関数テンプレートが呼び出される

*/

