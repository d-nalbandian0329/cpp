// Policy-based Design
// This method makes it possible to select
// process used in class at compile time.
// Policy means switchable process of class.

// Policy-based Design and Strategy Design Pattern are
// often compared, because the purpose of them is same. 
// It is "Switch the process".

// In Strategy pattern, use inheritance for switching process.
// In Policy-based Design, use template parameter for
// switching process.

// This is sample program for policy-based design.



#include <iostream>
#include <string>
#include <fstream>


struct debug_log {
	static void print(const std::string& value) {
		std::cout << value << std::endl;
	}
};

struct release_log {
	static void print(const std::string&) {}
};


struct file_log {
	static void print(const std::string& value) {
		std::ofstream ofs("./log.txt", std::ios::out);
		ofs << value << std::endl;
	}
};


// This class is switched process by template parameter.
// And release_log, file_log, file_log are called Policy class.
template <class LogPolicy>
struct hoge {
	void foo() const {
		LogPolicy::print("Fatal Error!!");
	}
};

int main() {
	hoge<debug_log>().foo();
	hoge<release_log>().foo();
	hoge<file_log>().foo();
}

