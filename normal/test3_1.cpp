#include <iostream>
#include <vector>
#include <list>

template <class Iterator, class T>
Iterator test_find(Iterator first, Iterator last, const T& value){
	while(first != last) {
		if(*first == value)
			break;
		++first;
	}

	return first;
}


int main() {
	using namespace std;

	char ary[] = "hello,world";
	vector<int> vec = { 1, 2, 3 };
	list<long> lst = { 1L, 2L, 3L };

	char *p = test_find(begin(ary), end(ary), ',');
	if(p != end(ary))
		std::cout << *p << " is found!" << std::endl;

	decltype(vec)::iterator v_ite = test_find(begin(vec), end(vec), 3);
	if(v_ite != end(vec))
		std::cout << *v_ite << " is found!" << std::endl;

	decltype(lst)::iterator l_ite = test_find(begin(lst), end(lst), 3L);
	if(l_ite != end(lst))
		std::cout << *l_ite << " is found!" << std::endl;

	return 0;
}



/*
使い方が違うwww
int main() {
	int a[] = { 1, 2, 3, 4, 5 };

	auto ret = test_find(&a[0], &a[(sizeof(a)/sizeof(decltype(a[0]))-1)], 2);

	std::cout << *ret << std::endl;
}
*/
