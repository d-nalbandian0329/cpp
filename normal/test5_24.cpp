// Optimization for avoiding unneccesary destructor call.
// If user construct an object using new operator,
// must call destructor to destruct it.
// But if the object is premitive type, e.g. int, char,
// user need not to call destructor.

// ex.) std::vector
// This optimization is done in container class like std::vector.
// std::vector does following processes individually
// with allocator.
// 1. Allocate memory.
// 2. Free allocated memory.
// 3. Call constructor of each element of container.
// 4. Call destructor of each element of container.

/*
// Call destructor of each element.
while(first != last){
	first->~T();
	++first;
}
*/

// Switch destruction process.

#include <iostream>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>
#include <string>
#include <memory>

// boost::enable_if is higher-order metafunction.
template <class T,
	typename boost::enable_if<
		boost::has_trivial_destructor<T>
	>::type* = nullptr>
void destroy_all(T*, T*) {
	std::cout << "Don't destroy." << std::endl;
}

template <class T,
	typename boost::disable_if<
		boost::has_trivial_destructor<T>
	>::type* = nullptr
>
void destroy_all(T* first, T* last) {
	std::cout << "Loop destroy." << std::endl;
	while(first != last) {
		first->~T();
		++first;
	}
}


template <class T>
void construct_all(T* first, T* last) {
	while(first != last) {
		new (first) T();
		++first;
	}
}

template <class T>
void f() {
	std::allocator<T> alloc;

	std::size_t size = 3;

	T* ar = alloc.allocate(size, nullptr);

	construct_all(ar, ar + size);

	destroy_all(ar, ar + size);

	alloc.deallocate(ar, size);
}

int main() {
	f<std::string>();
	f<int>();
}

