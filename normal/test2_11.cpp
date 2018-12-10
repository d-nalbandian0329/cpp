#include <iostream>
#include <string>

template <class T, int N>
int size(T (&ary)[N]) {
	return N;
}

template <class T, int N>
T last_element(T (&ary)[N]) {
	return ary[N-1];
}

int main() {
	int data[] = { 1, 3, 5, 7, 9 };
	// size<int,5> と解釈される 
	int n = size(data);
	// last_element<int,5>と解釈される
	int last = last_element(data);

	std::cout << "size : " << n << std::endl;
	std::cout << "last : " << last << std::endl;
}

