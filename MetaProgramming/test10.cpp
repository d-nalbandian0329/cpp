#include <iostream>
#include <utility>


template <class ConverterPolicy>
struct Converter {
	template <class Ptr>
	static auto convert(Ptr ptr, std::size_t all_size) {
		return ConverterPolicy::convert(std::forward<Ptr>(ptr), all_size);
	}
};






