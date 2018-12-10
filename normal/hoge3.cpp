// Optimize copy method by metafunction.

#include <iostream>
#include <cstring>
#include <iterator>
#include <type_traits>
#include <boost/type_traits/has_trivial_assign.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>

// If T is trivial assignableand destructorable,
// use std::memmove for copy.
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
	return (out + (last - first));
}


template <class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last,
					OutputIterator out) {
	std::cout << "Loop copy" << std::endl;
	while(first != last)
		*out++ = *first++;
	return out;
}


#include <vector>
#include <list>

auto main() -> int {
	int a1[] {3,1,4};
	int a2[3];
	::copy(std::begin(a1), std::end(a1), std::begin(a2));

	std::vector<int> v1 {3,1,4};
	std::vector<int> v2(3);
	::copy(std::begin(v1), std::end(v1), std::begin(v2));

	std::list<int> l1 {3,1,4};
	std::list<int> l2;
	::copy(std::begin(l1), std::end(l1), std::begin(l2));
}

