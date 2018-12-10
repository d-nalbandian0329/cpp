#include <iostream>
#include <string>
#include <cstring>
#include <boost/type_traits/has_trivial_assign.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>

namespace my {
	template <class Iterator,
				typename std::enable_if<
					std::is_pointer<Iterator>::value
					&& boost::has_trivial_assign<
						typename std::iterator_traits<Iterator>::value_type
					>::value
					&& boost::has_trivial_destructor<
						typename std::iterator_traits<Iterator>::value_type
					>::value
				>::type* = nullptr>
	Iterator copy(Iterator first, Iterator last, Iterator out) {
		std::cout << "std::memmove" << std::endl;
		std::memmove(out, first, (last - first) * sizeof(decltype(*first)));
		return out + (last - first);
	}

	template <class InputIterator, class OutputIterator>
	OutputIterator copy(InputIterator first, InputIterator last,
						OutputIterator out) {
		std::cout << "while loop" << std::endl;
		while(first != last)
			*out++ = *first++;

		return out;
	}
}


template <class Container>
void print(const std::string& pre_str, const Container& container) {
	std::cout << pre_str;
	for(auto e : container)
		std::cout << " " << e;
	std::cout << std::endl;
}


#include <list>

int main() {
	int ary1[] = {3,1,4};
	int ary2[3];
	my::copy(std::begin(ary1), std::end(ary1), std::begin(ary2));

	print("ary1 :", ary1);
	print("ary2 :", ary2);

	std::list<int> ls1 = {3,1,4};
	std::list<int> ls2(3);
	my::copy(std::begin(ls1), std::end(ls1), std::begin(ls2));

	print("ls1  :", ls1);
	print("ls2  :", ls2);

	return 0;
}

