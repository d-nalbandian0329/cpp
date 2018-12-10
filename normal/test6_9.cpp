// Policy-based design with non-static member funcion.

// This design is represented following two method.

// 1. Define policy-class object as member variable in policy-handler-class.

// 2. Inheritance policy-class, and define member function specified to
//    switch process.

#include <iostream>

class policy {
protected:
	void func() const {
		std::cout << "policy func()" << std::endl;
	}
};

class policy2 {
	int value_;

protected:
	int func() {
		std::cout << "policy2 func()" << std::endl;
		value_ = 100;
		std::cout << "value : " << value_ << std::endl;
		return value_;
	}
};



// 1. Template inheritance with policy-class.
//    So this class take over member of policy-class.
// 2. As mentioned above, policy-handler-class can control
//    kind and number of member function, each type of template parameter.

// Policy-handler-class : Define abstract member function that can be used
//						  for any purpose.

// Policy-class         : Define member function specified to be chageable.

template <class Policy>
class widget : public Policy {
public:
	void do_something() {
		func();
	}
};


auto main() -> int {
	widget<policy>  obj1;
	widget<policy2> obj2;

	obj1.do_something();
	obj2.do_something();
}


// Ths design is used in Boost.Multi-Index
// that make container have multi-sequence.

// boost::multi_index_container switches available member function
// depending on specified policy.

// ex.)
// If you set sequenced policy to it, it will be able to use push_back()
// member function.
// !! sequenced means that elements of container lined up
//    in order of insertion.

// On the other hand, if you set order_unique, it will be abale to
// use insert() member function instead of push_back().
// !! order_unique means that the container is already sorted.


