// http://fimbul.hateblo.jp/entry/2013/07/20/042822
// metafunction is_same の実装


// integral_constant wraps static constant of specified type.
// it is the base class for the base classfor the C++ type traits.

// Two specializations for he type bool are provided.

#include <iostream>

namespace my {
	template <class T, T v>
	struct integral_constant {
		static constexpr T value = v;
		using type = integral_constant<T, v>;
		constexpr operator T () const { return v; }
	};

	using true_type = integral_constant<bool, true>;
	using false_type = integral_constant<bool, false>;

	template <class T, class S>
	struct is_same {
		static constexpr bool value = false;
		using type = false_type;
	};

	template <class T>
	struct is_same <T, T> {
		static constexpr bool value = true;
		using type = true_type;
	};
}


auto main() -> int {
	std::cout << std::boolalpha;
	std::cout << "int,int      : " << my::is_same<int,int>::value << std::endl;
	std::cout << "int,uint32_t : " << my::is_same<int,uint32_t>::value << std::endl;
}

