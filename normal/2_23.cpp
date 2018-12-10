#include <iostream>
#include <typeinfo>

using namespace std;

void printType() {
	cout << endl;
}

// 最初の呼び出し時では
// THead => char
// TBody => int, const char*
template <class THead, class... TBody>
void printType(THead head, TBody... body) {
	cout << '(' << typeid(THead).name() << ')' << head;

	// sizeof...(body) bodyに含まれる型の数
	if(sizeof...(body) > 0)
		cout << ", ";

	// body... によってパラメータパックの展開を行う
	// printType<int, const char*>(4, "two"); がインスタンス化される
	// 最終的にパラメータパックの中の型が0個になって
	// その関数呼び出しに一致する関数は上で宣言・定義されている
	// 通常関数 void printType();になる
	printType(body...);
}



int main() {
	// printType<char, int, const char*>() がインスタンス化される
	printType('T', 4, "Two");
	return 0;
}

