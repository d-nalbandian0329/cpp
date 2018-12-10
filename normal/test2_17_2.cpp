#include <iostream>
#include <string>

template <class T>
class Printer {
public:
	void out(const T& t) const {
		std::cout << t << std::endl;
	}
};

// テンプレートパラメータにstring型を与えられた時の処理を分岐するため
// テンプレートの明示的特殊化を行う
template <>
class Printer<std::string> {
public:
	void out(const std::string& t) const {
		std::cout << "\"" << t << "\"" << std::endl;
	}
};

int main(){
	Printer<int> pi;
	Printer<std::string> ps;

	pi.out(10);
	ps.out(std::string("10"));

	return 0;
}

