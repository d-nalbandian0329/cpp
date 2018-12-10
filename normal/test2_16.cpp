#include <iostream>

template <class T>
int foo(T x, int n){
	// template限定子によってget()がメンバ関数テンプレートであることを明示
	return x.template get<3>(n);
}

class utility {
public:
	template <int N>
	int get(int args){
		return N + args;
	}
};

int main(){
	utility x;
	std::cout << foo(x, 3) << std::endl;
}

