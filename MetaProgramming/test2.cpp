#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <memory>


class LCGenerator {
public:
	LCGenerator() {
		srand(time(NULL)),rand();
	}

	// Normal Psuedo Random Number by Linear Congruential Generators
	double normalRandom() {
		return (static_cast<double>(rand())/(RAND_MAX + 1.0));
	}
};

class MersenneTwister {
public:
	MersenneTwister() {
		std::random_device seedgen;
		mt = std::mt19937_64(seedgen());
	}

	double normalRandom() {
		return dist(mt);
	}

private:
	std::mt19937_64 mt;
	std::normal_distribution<> dist;
};


template <class Generator>
std::unique_ptr<double[]> makeRandomNumbers(Generator generator, std::size_t N) {
	std::unique_ptr<double[]> sequence(new double[N]);

	for(std::size_t i = 0; i < N; ++i)
		sequence[i] = generator.normalRandom();

	return std::move(sequence);
}


template <class Container>
double calculateMean(const Container& container, const std::size_t N) {
	double mean = 0.0;

	for(std::size_t i = 0; i < N; ++i)
		mean += (container[i] - mean) / (i + 1);

	return mean;
}

template <class Container>
double calculateVariance(const Container& container, double mean, const std::size_t N) {
	double variance = 0.0;
	int i = 0;

	for(std::size_t i = 0; i < N; ++i)
		variance += (std::pow((container[i] - mean),2) - variance) / (i + 1);

	return variance;
}


template <class Generator>
void process(const Generator& generator) {
	constexpr std::size_t N = 1000000;

	auto container = makeRandomNumbers(generator, N);

	double mean = calculateMean(container, N);

	double variance = calculateVariance(container, mean, N);

	std::cout << "mean     : " << mean << std::endl;
	std::cout << "variance : " << variance << std::endl;
}


void doAllProcess() {
	LCGenerator lc_gen;
	MersenneTwister mt_gen;

	std::cout << "=== Linear Congruential Generators ===" << std::endl;
	process(lc_gen);
	std::cout << "======================================\n" << std::endl;


	std::cout << "==== Mersenne Twister Generators ====" << std::endl;
	process(mt_gen);
	std::cout << "======================================\n" << std::endl;
}


auto main() -> int {
	doAllProcess();

	return 0;
}

