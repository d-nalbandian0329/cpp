#include <iostream>

using namespace std;


class X {
public:
	X(){ cout << "dctor" << endl; }

	~X(){}

	X(const X&){ cout << "copy ctor" << endl; }

	X(X&&){ cout << "move ctor" << endl; }
	
	X& operator=(const X&) { cout << "copy ope" << endl; }

	X&& operator=(X&&) { cout << "move ope" << endl; }

};



auto main() -> int {
	cout << "X x1, x2;" << endl;
	X x1, x2;

	cout << "x1 = x2;" << endl;
	x1 = x2;

	cout << "x1 = move(x2);" << endl;
	x1 = move(x2);

	cout << "X x3 = X();" << endl;
	X x3 = X();

	cout << "X x4 = x3;" << endl;
	X x4 = x3;

}

