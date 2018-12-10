#include <iostream>
#include <cstring>
#include <vector>
#include <type_traits>
#include <boost/type_traits/has_trivial_assign.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>


namespace my {
	template <class Iterator,
				typename std::enable_if<
					std::is_pointer<Iterator>::value
					&&
					boost::has_trivial_assign<
						typename std::iterator_traits<Iterator>::value_type
					>::value
					&&
					boost::has_trivial_destructor<
						typename std::iterator_traits<Iterator>::value_type
					>::value
				>::type* = nullptr>
	Iterator copy(Iterator first, Iterator last, Iterator out) {
		std::cout << "std::memove" << std::endl;
		std::memmove(out, first, (out - first) * sizeof(decltype(*first)));
		return out + (last - first);
	}

	template <class InputIterator, class OutputIterator>
	OutputIterator copy(InputIterator first, InputIterator last, OutputIterator out) {
		std::cout << "normal" << std::endl;

		while(first != last)
			*out++ = *first++;

		return out;
	}
}


int main() {
	int a[] {1, 2, 3, 4};
	int b[4];

	my::copy(std::begin(a), std::end(a), std::begin(b));

	std::vector<int> av {1, 2, 3, 4};
	std::vector<int> bv(av.size());

	my::copy(std::begin(av), std::end(av), std::begin(bv));

}




