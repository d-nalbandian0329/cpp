#include <iostream>

// This meta-function qualify type T to const lvalue reference.
template <class T>
struct const_lvalue_reference {
	typedef const T& type;
};

class Hoge {
	Hoge(int n) : n_(n) {
	}

public:
	static Hoge&& factory(int n) {
		return Hoge(n);
	}

	void show(){ std::cout << n_ << std::endl; }

	int n_;
};

int main() {
	const_lvalue_reference<Hoge> h = Hoge::factory(1234);

	h.show();

	return 0;
}

