#include <iostream>
#include <chrono>
#include <memory>


template <class Predicate, class TimeType>
auto measureTime(Predicate predicate, TimeType timetype) -> TimeType {
	auto start = std::chrono::system_clock::now();

	predicate();

	auto end = std::chrono::system_clock::now();

	return std::chrono::duration_cast<TimeType>(end - start);
}


template <class T>
std::unique_ptr<T[]> makeUniqueArray(std::size_t n) {
	n = (n > 0 ? n : 1);
	return std::move(std::unique_ptr<T[]>(new T[n]));
}


void doAllProcess() {
	constexpr std::size_t N = 100;

	//auto array = makeUniqueArray<int>(N);

	auto func = std::bind(makeUniqueArray<int>, N);

	auto period = measureTime(func, std::chrono::microseconds());

	std::cout << "time : " << period.count() << std::endl;
}

auto main() -> int {

	doAllProcess();

	return 0;
}

