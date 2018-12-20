#include <iostream>
#include <typeinfo>

// RTTI(RunTime Type Information : 実行時型情報)
// 実行時にオブジェクトの型を調べることができる

// typeid 演算子
// オペランドに何らかの型名を与えるとその型情報への参照を返す
// 戻り値は const std::type_info&

namespace n1 {
	class X {};

	class Y : public X {};

	void test1() {
		std::cout << typeid(X).name() << std::endl;
	}

	void test2() {
		X* p = new Y;
		std::cout << typeid(*p).name() << std::endl;
	}
}


namespace n2{
	class Base { virtual void f() {} };
	class Derived1 : public Base {};
	class Derived2 : public Base {};

	void test() {
		// ポインタを他のクラスを指すように変換するとメモリアドレスの調整
		// が必要になる可能性がある, 故にreinterpret_castがビットレベルで
		// 何も変更を加えないキャストであることから利用すべきでない
		// また継承構造内には派生クラスが一つであるとは限らないので
		// 兄弟となるクラス間のクロスキャストを行う際にもdynamic_castを
		// 利用できる
		Base* const bp = new Derived1;

		// ダウンキャストを行う
		// dynamic_castによるダウンキャストを機能させるためには仮想関数が
		// 含まれている必要がある
		// 必然的にdynamic_castの対象は継承構造を持ったオブジェクトを指す
		// ポインタか参照
		// Errorしたとき
		// pointer   : 変換先のポインタ型で表現されるnull pointer
		// reference : std::bad_cast例外が送出される
		Derived2* const pd = dynamic_cast<Derived2*>(bp);
		if(pd == nullptr) {
			std::cout << "Error" << std::endl;
		}
		else {
			std::cout << "OK" << std::endl;
		}

		try {
			Derived2& rd = dynamic_cast<Derived2&>(*bp);
			std::cout << "OK" << std::endl;
		}
		catch(std::bad_cast&) {
			std::cout << "Error" << std::endl;
		}

		delete bp;
	}


}



int main() {
	/*
	{
		n1::test1();
		n1::test2();
	}
	*/

	{
		n2::test();	
	}
}

