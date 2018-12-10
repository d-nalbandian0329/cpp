// Optimize function implementation by SFINAE.
// Overloading resolution with SFINAE can be
// used for optimization.

// std::copy : Copy from specified range to another range.

/*
std::memmove

Defined header <cstring>
void* memmove(void* dest, const void* src, size_t count);

Copies count characters from the object pointed to by src
to the object pointed to by dest.

Both objects are reinterpreted as array of unsigned char.

The objects may overlap: copying takes place as if the characters



Parameters
dest  : pointer to the memory location to copy to
src   : pointer to the memory location to copy from
count : number of bytes to copy

Return value : dest

*/

#include <iostream>
#include <cstring>
#include <boost/type_traits/has_trivial_assign.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>

template <class Iterator,
	typename std::enable_if<
		std::is_pointer<Iterator>::value
		&& boost::has_trivial_assign<
			typename std::iterator_traits<Iterator>::value_type
		>::value
		&& boost::has_trivial_destructor<
			typename std::iterator_traits<Iterator>::value_type
		>::value
	>::type* = nullptr
>
Iterator copy(Iterator first, Iterator last, Iterator out) {
	std::cout << "memmove" << std::endl;

	std::memmove(out, first, (last - first) * sizeof(decltype(*first)));

	return (out + (last - first));
}

template <class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last, OutputIterator out) {
	while(first != last)
		*out++ = *first++;

	return out;
}


#include <list>

int main() {
	int ary1[] = {3,1,4};
	int ary2[3];

	::copy(std::begin(ary1), std::end(ary1), std::begin(ary2));
	std::cout << "ary1 :";
	for(int x : ary1)
		std::cout << " " << x;
	std::cout << std::endl;

	std::cout << "ary2 :";
	for(int x : ary2)
		std::cout << " " << x;
	std::cout << std::endl;


	std::list<int> ls1 {3,1,4};
	std::list<int> ls2(3);

	::copy(std::begin(ls1), std::end(ls1), std::begin(ls2));
	std::cout << "ls1 :";
	for(int x : ls1)
		std::cout << " " << x;
	std::cout << std::endl;

	std::cout << "ls2 :";
	for(int x : ls2)
		std::cout << " " << x;
	std::cout << std::endl;

	return 0;
}

