// コンテナを継承してパラメータ化継承によってメンバを追加する
#include <iostream>
#include <vector>
#include <list>

template <class Base>
class Printable : public Base {
public:
	using Base::Base;

	std::ostream& print_on(std::ostream& stream,
							const char* delim = " ") const {
		for (const auto& x : *this) {
			stream << x << delim;
		}
		return stream;
	}
};

int main() {
	using namespace std;

	Printable<vector<int>> pv { 1, 2, 3 };
	Printable<list<int>> pl { 4, 3, 2 };

	pv.print_on(std::cout) << std::endl;
	pl.print_on(std::cout, ",") << std::endl;

	return 0;
}

