#include <iostream>
#include <vector>
#include <iterator>

namespace my {
	template <class Iterator, class Predicate>
	Iterator find_if(Iterator first, Iterator last, Predicate pred) {
		while(first != last){
			if(pred(*first))
				break;
			++first;
		}

		return first;
	}

	// functor / function object
	struct is_even {
		bool operator()(int x) const {
			return x % 2 == 0;
		}
	};

	template <class Container, class Predicate>
	void func(const Container& vec, Predicate pred, const std::string& msg) {
	}	
}

auto main() -> int {
	using namespace std;

	vector<int> vec { 1, 2, 3, 4 };

	{
		decltype(vec)::iterator ite = my::find_if(std::begin(vec), std::end(vec), my::is_even());
		std::cout << "Even :";
		while(ite != std::end(vec)){
			std::cout << " " << *ite;
			ite = my::find_if(++ite, std::end(vec), my::is_even());
		}
		std::cout << std::endl;
	}


	{
		auto is_odd = [](int x) -> bool { return x%2!=0; };

		decltype(vec)::iterator ite = my::find_if(std::begin(vec), std::end(vec), is_odd);
		std::cout << "Odd  :";
		while(ite != std::end(vec)){
			std::cout << " " << *ite;
			ite = my::find_if(++ite, std::end(vec), is_odd);
		}
		std::cout << std::endl;
	}

	return 0;
}

