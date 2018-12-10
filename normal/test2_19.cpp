#include <iostream>
#include <string>

template <class T>
class Printer {
public:
	void out(const T& value) const {
		std::cout << value << std::endl;
	}
};

template <class T>
class Printer<T*> {
public:
	void out(const T* value) const {
		std::cout << *value << std::endl;
	}
};

// 関数テンプレートは部分特殊化が許可されていないので
// オーバーロードで代用する

template <class T>
void print(const T value){
	std::cout << value << std::endl;
}

template <class T>
void print(T* value){
	std::cout << *value << std::endl;
}


int main(){
	int n = 3;
	Printer<int*> pip;
	pip.out(&n);

	int n2 = 123;
	print(n2);
	print(&n2);
}

