#include <iostream>

class X {
public:
	X() {
		std::cout << "Default Constructor." << std::endl;
	}

	X(const X&) {
		std::cout << "Copy Constructor." << std::endl;
	}

	X(X&&) {
		std::cout << "Move Constructor." << std::endl;
	}

	X& operator=(const X& other) & {
		std::cout << "Copy Operator." << std::endl;

		return *this;
	}

	X& operator=(X&& other) & {
		std::cout << "Move Operator RL." << std::endl;

		return *this;
	}

	X&& operator=(X&& other) && {
		std::cout << "Move Operator RR." << std::endl;

		return std::move(*this);
	}
};

X rvo() {
	return X();
}

X nrvo() {
	X temp;
	return temp;
}


int main() {
	using namespace std;

	cout << "\nX obj;" << std::endl;
	X obj;

	cout << "\nX();" << std::endl;
	X();

	cout << "\nX obj2 = X();" << std::endl;
	X obj2 = X();

	cout << "\nX obj3 = obj2;" << std::endl;
	X obj3 = obj2;

	cout << "\nX obj4 = rvo();" << std::endl;
	X obj4 = rvo();

	cout << "\nX obj5 = nrvo();" << std::endl;
	X obj5 = nrvo();

	cout << "\nX obj6(obj5);" << std::endl;
	X obj6(obj5);

	std::cout << "\nobj6 = std::move(obj5);" << std::endl;
	obj6 = std::move(obj5);

	std::cout << "\nX() = std::move(obj6);" << std::endl;
	X() = std::move(obj6);

/*
	cout << "X obj7(X());" << std::endl;
	X obj7(X());

	cout << "X obj8(std::move(obj7));" << std::endl;
	X obj8(std::move(obj7));
*/
}


