#include <iostream>
#include <iterator>
#include <vector>
#include <type_traits>
#include <functional>

template <class Iterator>
void print(Iterator first, Iterator last, const std::string& msg){
	std::cout << msg;
	while(first != last){
		std::cout << " " << *first;
		++first;
	}
	std::cout << std::endl;
}

template <class Iterator, class Predicate>
void selection_sort(Iterator first, Iterator last, Predicate pred) {
	for(Iterator i = first; i != last; ++i){
		Iterator min = i;

		for(Iterator j = i; j != last; ++j){
			if(pred(*j, *min))
				min = j;
		}

		//auto tmp = *i;
		typename std::remove_reference<decltype(*i)>::type tmp = *i;
		*i = *min;
		*min = tmp;
	}
}

template <class Predicate>
void test(const std::vector<int>& v, Predicate pred) {
	std::remove_const<std::remove_reference<decltype(v)>::type>::type vec = v;

	print(begin(vec), end(vec), "Before :");

	selection_sort(begin(vec), end(vec), pred);

	print(begin(vec), end(vec), "After  :");
}



int main() {
	using namespace std;

	vector<int> vec { 10, 2, 1, 3, 5, 9, 4, 7, 6, 8 };
	test(vec, [](int n1, int n2){ return n1 < n2; });

	test(vec, std::greater<int>());

	return 0;
}

