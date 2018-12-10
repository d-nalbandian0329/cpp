#include <iostream>
#include <vector>

template <template <class T, class Allocator=std::allocator<T>> class Container>
void showContents(const Container<double>& container) {
	for(std::size_t i = 0; i < container.size(); ++i)
		std::cout << container[i] << std::endl;
}


int main() {
	std::vector<double> v { 1,2,3,4,5 };

	showContents(v);

	return 0;
}

