#include <iostream>
#include <numeric>
#include <algorithm>
#include <chrono>
#include <random>
#include <utility>
#include <functional>


template <
	class T,
	template <class E, class Allocator = std::allocator<E>>
	class Container
>
double getMean(const Container<T>& container) {
	double mean = 0.0;
	int i = 0;
	auto ope = [&](double mean, double e) -> double {
		return mean + (e - mean) / ++i;
	};
	return std::accumulate(std::begin(container), std::end(container), mean, ope);
}




template <
	class T,
	template <class E, class Allocator = std::allocator<E>>
	class Container
>
double getVariance(const Container<T>& container, double mean) {
	double variance = 0.0;
	int i = 0;
	auto ope = [&](double variance, double e) -> double {
		return variance + (std::pow(e - mean, 2) - variance) / ++i;
	};
	return std::accumulate(std::begin(container), std::end(container), variance, ope);
}


template <
	class T,
	template <class E, class Allocator = std::allocator<E>>
	class Container
>
double getVariance(const Container<T>& container) {
	return getVariance(container, getMean(container));
}


template <
	class T,
	template <class E, class Allocator = std::allocator<E>>
	class Container
>
Container<T> generateData(Container<T>&& container) {
	std::random_device seed_gen;
	std::mt19937_64 mt { seed_gen() };
	std::normal_distribution<> normal_dist { 0.0, 1.0 };

	auto gen = [&]() -> double { return normal_dist(mt); };
	std::generate(std::begin(container), std::end(container), gen);

	return std::move(container);
}


void doAllProcess() {
	constexpr int N = 1000000;

//	std::vector<int> v(N);
//	std::iota(std::begin(v), std::end(v), 1);

	std::vector<double> v(N);

	double mean, variance;

	using TimeType = std::chrono::microseconds;
	const std::string unit_str(" [micro sec]");

	{
		v = generateData(std::move(v));
		auto start = std::chrono::high_resolution_clock::now();
		mean = getMean(v);
		std::cout << "\nmean     : " << mean << std::endl;
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << "period   : "
			<< std::chrono::duration_cast<TimeType>(end - start).count() << unit_str << std::endl;
	}

	{
		v = generateData(std::move(v));
		auto start = std::chrono::high_resolution_clock::now();
		variance = getVariance(v);
		std::cout << "\nvariance : " << variance << std::endl;
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << "period   : "
			<< std::chrono::duration_cast<TimeType>(end - start).count() << unit_str << std::endl;
	}

	{
		v = generateData(std::move(v));
		auto start = std::chrono::high_resolution_clock::now();
		variance = getVariance(v, mean);
		std::cout << "\nvariance : " << variance << std::endl;
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << "period   : "
			<< std::chrono::duration_cast<TimeType>(end - start).count() << unit_str << std::endl;
	}
}



auto main() -> int {
	doAllProcess();
	return 0;
}

