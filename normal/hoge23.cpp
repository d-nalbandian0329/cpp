#include <iostream>
#include <array>

template <int N>
struct StaticConvert {
	//static const std::string digit("0" + N%10);
	static const std::string value
		= std::string(StaticConvert<N/10>::value + const std::string("0" + N%10));
};

template <>
struct StaticConvert<0> {
	static const std::string value = std::string("");
};

int main() {
	std::array<const std::string, 2> s {"hoge", "fuga"};

	std::cout << s[0] << std::endl;
	std::cout << s[1] << std::endl;

	std::cout << StaticConvert<1232>::value << std::endl;
}

