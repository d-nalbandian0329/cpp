#include <iostream>
#include <vector>
#include <iterator> // begin, end, back_inserter

template <class InputIterator, class OutputIterator>
OutputIterator mycopy(InputIterator first, InputIterator last,
					OutputIterator out) {
	while(first != last) {
		*out = *first;
		++out,++first;
	}
	return out;
}


int main() {
	using namespace std;

	vector<int> v = { 1, 2, 3 };

	vector<int> ret;

	// Use forward iterator as OutputIterator.
	// Don't forget to allocate enough storage, before call mycopy.
	vector<int> ret2(v.size());

	mycopy(begin(v), end(v), back_inserter(ret));

	mycopy(begin(v), end(v), begin(ret2));

	cout << "back_insert_iterator\n=>";
	for(int x : ret)
		cout << " " << x;
	cout << endl;

	cout << "random access iterator\n=>";
	for(auto x : ret2)
		cout << " " << x;
	cout << endl;

	return 0;
}

