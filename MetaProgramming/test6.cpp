#include <iostream>
#include <type_traits>

namespace my {
	struct is_same_impl {
		template <class T>
		static auto check(T*, T*) -> std::true_type;

		template <class T, class U>
		static auto check(T*, U*) -> std::false_type;
	};


	template <class T, class U>
	class is_same
		: public decltype(is_same_impl::check(std::declval<T*>(),
											std::declval<U*>())) {
	};
}

auto main() -> int {
	{
		std::cout << std::boolalpha;
		std::cout << "int,int    : " << my::is_same<int,int>::value << std::endl;
		std::cout << "int,double : " << my::is_same<int,double>::value << std::endl;
	}
}

