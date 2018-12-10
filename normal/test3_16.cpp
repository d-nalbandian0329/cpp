#include <iostream>
#include <vector>
#include <list>
#include <utility>


// 範囲指定されたイテレータペアを用いて内容を出力
template <class Iterator>
void print_all(std::pair<Iterator,Iterator> iter_pair) {
	while(iter_pair.first != iter_pair.second){
		std::cout << " " << *(iter_pair.first);
		++(iter_pair.first);
	}
	std::cout << std::endl;
}

int main() {
	int ary[] = { 1, 2, 4, 8, 16 };

	std::vector<int> v(std::begin(ary), std::end(ary));

	// クラステンプレートは引数からの型推論ができないので
	// そのまま使うとコード記述が大変
	print_all(std::pair<int*, int*>(std::begin(ary), std::end(ary)));
	print_all(std::make_pair(std::begin(ary), std::end(ary)));

	print_all(std::pair<std::vector<int>::iterator,
						std::vector<int>::iterator
						>(std::begin(v), std::end(v)));
	print_all(std::make_pair(std::begin(v), std::end(v)));


	return 0;
}

