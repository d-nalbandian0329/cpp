#include <iostream>
#include <iterator>
#include <list>
#include <vector>


int main() {
	using namespace std;

	vector<int> v { 1, 2, 3 };
	list<int> lst { 1, 2, 3 };

	decltype(v)::iterator vi = std::begin(v);
	advance(vi, 2);
	std::cout << *vi << std::endl;

	decltype(lst)::iterator li = std::begin(lst);
	if(li == std::end(lst))
		std::cout << "end" << std::endl;
	else
		std::cout << *li << std::endl;

	return 0;
}

