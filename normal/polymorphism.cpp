#include <iostream>
#include <type_traits>
#include <typeinfo>


template <class T>
class Interface;


template <class T, bool isExtended = std::is_base_of<Interface<T>,T>::value>
class Printer {
	static_assert(isExtended, "T is not derived from Interface<T>.");
};

template <class T>
class Printer<T, true> {
	T _obj;

public:
	void print(){ _obj.print(); };
};


template <class T>
class Interface {
public:
	void print() {
		std::cout << "Interface print()" << std::endl;
		static_cast<T&>(*this).print();
	}
};


class myclass1 : public Interface<myclass1> {
public:
	void print() {
		std::cout << "myclass1 print()" << std::endl;
	}
};

class myclass2 : Interface<myclass2> {
public:
	void print() { std::cout << "myclass2" << std::endl; }
};

class myclass3 : Interface<myclass3> {
};

class myclass4 {
public:
	void print() { std::cout << "myclass4" << std::endl; }
};


// trailing return type syntax.
auto main() -> int {
	Printer<myclass1> a;
	Printer<myclass2> b;
	Printer<myclass3> c;
//	Printer<myclass4> d;

	a.print();
	b.print();
//	c.print();

	Interface<myclass1> m1;

	m1.print();

	std::cout << "m1 : " << typeid(m1).name() << std::endl;

	return 0;
}

