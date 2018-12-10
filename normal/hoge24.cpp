#include <iostream>
#include <vector>
#include <list>
#include <array>


template <
	class T,
	template <class E, class Allocator = std::allocator<T>>
	class Container
>
void func(const Container<T>& container) {
	std::cout << "data :";
//	for(int i = 0; i < container.size(); ++i)
//		std::cout << " " << container[i];
	for(auto ite = std::begin(container); ite != std::end(container); ++ite)
		std::cout << " " << *ite;
	std::cout << std::endl;
}


int main() {
	std::vector<int>  v {1, 2, 3};
	std::list<int>    l {4, 5, 6};
	std::array<int,3> a {{7, 8, 9}};
	//int ary[] {10,11,12};

	func(v);
	func(l);
	func(a);
	//func(ary);
}

