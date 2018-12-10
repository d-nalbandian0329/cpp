#include <iostream>
#include "stack.h"

/*
各コードをコンパイルすると成功するがリンクエラーが発生する
main.cpp内でStack<int>を使用したことがstack.cppまで伝わらないため
=> stack.cppにmain.cppで使用したテンプレート引数が
   intであることを伝えられないため

そこでmain.cppで使用するテンプレート引数がintであることが
あらかじめわかっている場合はstack.cppの末尾に

template class Stack<int>;

を記述することでStack<int>の明示的インスタンス化が行われて
リンクに成功する
*/


int main(){
	Stack<int> s(10);
	s.push(1);
	s.push(2);

	while(s.size() != 0){
		std::cout << s.top() << std::endl;
		s.pop();
	}

	return 0;
}

