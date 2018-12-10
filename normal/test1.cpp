#include <iostream>
#include <algorithm>
#include <memory>
#include <string>
#include <type_traits>

struct Magica {
	virtual std::string call() const = 0;
};

struct Madoka : Magica {
	std::string call() const { return "ﾎﾑﾗﾁｬﾝ!"; }
};

struct Homura : Magica {
	std::string call() const { return "ﾏﾄﾞｶｧ!"; }
};


struct Incubator {
	template <
		class T,
		class C = typename std::enable_if<std::is_base_of<Magica,T>::value>::type
	>
	static std::unique_ptr<Magica> create() {
		return std::unique_ptr<Magica>{ new T{} };
	}
};


auto main() -> int {
	const auto girls = { Incubator::create<Madoka>(), Incubator::create<Homura>() };

	std::for_each(std::begin(girls), std::end(girls),
					[](const std::unique_ptr<Magica>& girl){
						std::cout << (*girl).call() << std::endl;
					}
	);

	return 0;
}

