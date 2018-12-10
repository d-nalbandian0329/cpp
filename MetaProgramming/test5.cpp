#include <iostream>

namespace my {
	template <class T, T v>
	struct integral_constant {
		static constexpr T value = v;
		using value_type = T;
		using type = integral_constant<T,v>;
		constexpr operator T() const { return v; }
	};

	using true_type = integral_constant<bool,true>;
	using false_type = integral_constant<bool,false>;

	template <class S, class T>
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


int main() {
	std::cout << std::boolalpha;
	std::cout << "int,int  : " << my::is_same<int,int>::value << std::endl;
	std::cout << "int,char : " << my::is_same<int,char>::value << std::endl;
}

