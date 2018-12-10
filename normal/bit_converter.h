#ifndef __BIT_CONVERTER_H__
#define __BIT_CONVERTER_H__

#include <iostream>
#include <cstring>
#include <type_traits>


template <class ConverterPolicy>
class BitConverter {
public:
	auto convert(T&& obj) {
		return std::move(ConverterPolicy::convert(std::forward<T>(obj)));
	}
};


class ArithmeticBitConverter {
public:
	template <class T>
	auto convert(T&& value) {
		static_assert(std::is_arithmetic<T>::value,
						"In ArithmeticBitConverter::converter<T>, T must be arithmetic type.\n");

		void* ptr = &value;

		std::array<uint8_t, sizeof(T)> bytes {};
		for(std::size_t i = 0; i < sizeof(T); ++i)
			bytes[i] = *(reinterpret_cast<uint8_t*>(ptr) + i) & 0xffu;

		return std::move(bytes);
	}
};


#endif	// __BIT_CONVERTER_H__

