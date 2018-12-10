#include <iostream>
#include <utility>
#include <memory>

using namespace std;

class HighCost {
public:
	double n[10000];
};

template <class T, int N>
constexpr int arraySize(T (&)[N]) {
	return N;
}


auto func(unique_ptr<HighCost>&& param) -> decltype(param) {
	for(int i = 0; i < arraySize(param->n); ++i)
		param->n[i] = i;

	return std::move(param);
}

unique_ptr<HighCost> factorial() {
	unique_ptr<HighCost> param(new HighCost());

	for(int i = 0; i < arraySize(param->n); ++i)
		param->n[i] = i;

	return param;
}


auto main() -> int {
	auto ret = factorial();

	for(int i = 0; i < arraySize(ret->n); i += 1000)
		std::cout << ret->n[i] << std::endl;

	return 0;
}

