#include <iostream>

// list initialization では縮小変換が許されない


void f(double val, int val2) {
	int x2 = val;   // If val2==7.9, x2==7
	char c2 = val2; // if val2 == 1025, c2 == 1

	// int x3 {val};     // Error:切り捨ての可能性
	// char c3 { val2 }; // Error:縮小の可能性

	char c4 {24};  // 24は8bitで正確に表現できるのでおｋ
	// char c5 {264}; // char 8bit なら264は表現できない

	// int x4{3.0}; // doubleからintへ変換できない

	// autoを利用して初期化子に基づいて型を取り出す場合
	// {} を使うとデメリットが大きい

	// auto z1 {99};  // z1はstd::initializer_list<int>型
	// auto z2 = 99;  // z2はint型

	// vector<int> v{99};  // 99を要素として持つベクトル
	// vector<int> v(99);  // 要素をデフォルト値0をもつ99個の要素
						   // から構成されるベクトル

	// デフォルト値で初期化をしたい場合は {} を用いる
	// int x {};         0
	// double y{};       0.0
	// char *cp {};      nullptr
	// vector<int> v {}; 空のベクトル
	// string str {};    ""
}


auto main() -> int {
	f(7.9, 1025);

	return 0;
}

