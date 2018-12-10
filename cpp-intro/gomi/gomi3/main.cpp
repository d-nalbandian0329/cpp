#include <iostream>

class Base {};

// Derived is-implemented-in-terms-of Base.
// 基底クラスへのポインタで派生クラスの実体を指すためには
// 基底クラスをpublic継承しないといけない
// class Derived : Base {};		// compile error
class Derived : public Base {};


int main() {
	Base* ptr = new Derived;
}

