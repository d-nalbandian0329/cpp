#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

void doAllProcess() {
	std::vector<int> v(5);
	std::iota(std::begin(v), std::end(v), 1);

	auto mean = std::accumulate(std::begin(v), std::end(v), 0) / v.size();
	auto proc = [=](double variance, double e){ return variance + std::pow(e - mean, 2); };
	auto variance = std::accumulate(std::begin(v), std::end(v), 0, proc) / v.size();

	std::cout << "mean     : " << mean << std::endl;
	std::cout << "variance : " << variance << std::endl;
}


int main() {
	doAllProcess();
}

