#include <iostream>
#include <vector>
#include <iterator>
#include <initializer_list>

template <class T>
struct Foo {
	Foo(){}

	Foo& operator=(std::initializer_list<T> list) {
		vec = std::vector<T>{};
		for(auto ite = list.begin(); ite != list.end(); ++ite)
			vec.push_back(*ite);
	}

	void print() {
		std::cout << "element :";
		for(auto ite = std::begin(vec); ite != std::end(vec); ++ite)
			std::cout << " " << *ite;
		std::cout << std::endl;
	}

	std::vector<T> vec;
};

int main() {
	Foo<int> foo;

	foo = { 1, 2, 3, 2, 4, 1, 15 };

	foo.print();

	return 0;
}

