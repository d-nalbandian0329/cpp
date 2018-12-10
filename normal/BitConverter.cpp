#include <iostream>
#include <iomanip>
#include <type_traits>
#include <memory>
#include <string>
#include <cstring>
#include <utility>


namespace my {
	struct X {
		X() : int_v(128), double_v(128), long_v(128) {
		};

		int int_v;
		double double_v;
		long int long_v;
	};
}


struct BitConverter_impl {
	template <class T>
	static auto convert(T value, typename std::enable_if<
								std::is_arithmetic<T>::value
							>::type* = nullptr)
		-> std::unique_ptr<uint8_t[]> {

		std::size_t type_size = sizeof(T);

		std::unique_ptr<uint8_t[]> byte_data(new uint8_t[type_size]);

		void* ptr = &value;
		for(std::size_t i = 0; i < type_size; ++i) {
			byte_data[i] = *(static_cast<uint8_t*>(ptr) + i) & 0xff;
		}

		return std::move(byte_data);
	}

	static auto convert(my::X obj) -> std::unique_ptr<uint8_t[]> {
		std::size_t all_size = sizeof(obj.int_v) + sizeof(obj.double_v) + sizeof(obj.long_v);

		std::unique_ptr<uint8_t[]> byte_data(new uint8_t[all_size]);
		int idx = 0;

		auto copy_data = [&](const std::unique_ptr<uint8_t[]>& buf, std::size_t nbyte) -> void {
			std::memcpy((byte_data.get()+idx), buf.get(), nbyte);
			idx += nbyte;
		};

		copy_data(BitConverter_impl::convert(obj.int_v), sizeof(obj.int_v));

		copy_data(BitConverter_impl::convert(obj.double_v), sizeof(obj.double_v));

		copy_data(BitConverter_impl::convert(obj.long_v), sizeof(obj.long_v));

		return std::move(byte_data);
	}

};

struct is_BitConvertable_impl {
	template <class T>
	static auto check(T*)
		-> decltype(BitConverter_impl::convert(std::declval<T>()), std::true_type());
							
	template <class T>
	static auto check(...) -> std::false_type;
};

template <class T>
class is_BitConvertable : public decltype(is_BitConvertable_impl::check<T>(nullptr)) {
};

class BitConverter : public BitConverter_impl {
public:
	template <class T>
	static auto convert(T value) -> std::unique_ptr<uint8_t[]> {
		static_assert(is_BitConvertable<T>::value,
						"BitConverter::convert don't support the type of parameter.");

		return std::move(BitConverter_impl::convert(value));
	}
};


void showValue(const std::unique_ptr<uint8_t[]>& byte_data, std::size_t type_size) {
	auto toBit = [](uint8_t value) -> std::string {
		std::string ret {};
		for(int i = 7; i >= 0; --i) {
			ret += ((value >> i) & 0x1u ? std::string("1") : std::string("0"));
		}
		return ret;
	};

	std::cout << "(" << type_size << " byte)\n";
	std::cout << "data :";
	for(int i = type_size - 1; i >= 0; --i) {
		std::cout << " " << toBit(byte_data[i]);
	}
	std::cout << std::endl << std::resetiosflags(std::ios_base::floatfield);
}





void doAllProcess() {
	{	
		int n { 32 };

		// The type of byte_data is std::unique_ptr<uint8_t[]>&&.
		auto&& byte_data = BitConverter::convert(n);

		showValue(byte_data, sizeof(n));
	}

	{	
		double n { 32 };

		// The type of byte_data is std::unique_ptr<uint8_t[]>&&.
		auto&& byte_data = BitConverter::convert(n);

		showValue(byte_data, sizeof(n));
	}

	{	
		my::X x;

		// The type of byte_data is std::unique_ptr<uint8_t[]>&&.
		auto&& byte_data = BitConverter::convert(x);

		showValue(byte_data, 16u);
	}
}


auto main() -> int {
	doAllProcess();	
}

