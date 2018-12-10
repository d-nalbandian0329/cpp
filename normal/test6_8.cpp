// Policy class that has non-static member function.
// The class handling policy-class has
// non-static member variable.
// If policy-class need to have state, use this method.

#include <iostream>

struct policy {
	void func() const {
		std::cout << "Do something." << std::endl;
	}
};


template <class Policy>
class widget {
	Policy obj;
public:
	void do_something() const {
		obj.func();
	}
};


auto main() -> int {
	widget<policy> w;

	w.do_something();

	return 0;
}

