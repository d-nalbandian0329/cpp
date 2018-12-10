// Policy class has static member function.

#include <iostream>

struct policy {
	static void foo() {
		std::cout << "policy foo()" << std::endl;
	}
};



template <class Policy>
struct widget {
	void do_something() {
		Policy::foo();
	}
};

auto main() -> int {
	widget<policy> w;

	w.do_something();

	return 0;
}

