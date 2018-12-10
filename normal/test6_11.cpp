// 

#include <iostream>
#include <string>


struct cout_policy {
	static void foo(const std::string& value) {
		std::cout << value << std::endl;
	}
};

struct printf_policy {
	static void foo(const std::string& value) {
		std::printf("%s\n", value.c_str());
	}
};


template <class Policy = cout_policy>
struct widget {
	void do_something(const std::string& value) {
		Policy::foo(value);
	}
};


// trailig return type syntax.
auto main() -> int {
	// Use default template parameter (cout_policy).
	widget<>().do_something("Default parameter.");

	// Use specified template parameter (printf_policy).
	widget<printf_policy>().do_something("Printf policy.");

	return 0;
}

