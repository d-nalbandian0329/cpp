#include <iostream>
#include <iterator>
#include <vector>
#include <list>


namespace my {
	// Bidirectional iterator, Random access iterator に
	// 対応するために負の数指定許可
	// ただしこれではRandom access iteratorの[]や+=, -=での
	// 効率的な移動に対応できない
	/*
	template <class Iterator, class Distance>
	void advance(Iterator ite, Distance offset) {
		if(offset >= 0) {
			for( ; offset > 0 --offset)
				++ite;
		}
		else {
			for( ; offset < 0 ++offset)
				--ite;
		}
	}
	*/

	// 前方向にイテレータを進める, 後ろ方向は不可
	template <class InputIterator, class Distance>
	void _advance(InputIterator& ite, Distance offset,
					std::input_iterator_tag) {
		for( ; offset > 0; --offset)
			++ite;
	}

	// 前方向にイテレータを進める, 後ろ方向は不可
	template <class ForwardIterator, class Distance>
	void _advance(ForwardIterator& ite, Distance offset,
					std::forward_iterator_tag) {
		for(; offset > 0; --offset)
			++ite;
	}

	// 双方向にイテレータを進める
	template <class BidirectionalIterator, class Distance>
	void _advance(BidirectionalIterator& ite, Distance offset,
					std::bidirectional_iterator_tag) {
		if(offset >= 0){
			for(; offset > 0; --offset)
				++ite;
		}
		else {
			for(; offset < 0; ++offset)
				--ite;
		}
	}

	// 双方向への移動, operator+=()で大幅な移動
	template <class RandomAccessIterator, class Distance>
	void _advance(RandomAccessIterator& ite, Distance offset,
					std::random_access_iterator_tag) {
		ite += offset;
	}

	template <class Iterator, class Distance>
	void advance(Iterator& ite, Distance offset) {
		my::_advance(ite, offset,
				typename std::iterator_traits<Iterator>::iterator_category());
	}


}


int main() {
	using namespace std;
	
	int a[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	auto ai = std::begin(a);

	vector<int> v {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	auto vi = std::begin(v);

	list<int> l {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	auto li = std::begin(l);

	my::advance(ai, 9);
	std::cout << *ai << std::endl;

	my::advance(vi, 3);
	std::cout << *vi << std::endl;

	my::advance(li, 4);
	std::cout << *li << std::endl;

	return 0;
}

