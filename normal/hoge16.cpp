#include <iostream>
#include <vector>
#include <random>

// Heaviside function.
int activateFunction(double input) {
	return (input > 0 ? 1 : 0);
}

int judge(const std::vector<double>& w, const std::vector<double>& x) {
	return activateFunction(w[0] * x[0] + w[1] * x[1] + w[2]);
}


bool check(const std::vector<double>& w, const std::vector<std::vector<double>>& x_set,
			const std::vector<double>& t) {

	for(int i = 0; i < x_set.size(); ++i) {
		if((t[i] > 0) == (judge(w, x_set[i]) > 0))
			return false;
	}

	return true;
}


void learning(std::vector<double>& w, const std::vector<double>& x, int t) {
	constexpr double eta = 0.15;
	int ret = activateFunction(w[0] * x[0] + w[1] * x[1] + w[2]);

	w[0] += eta * x[0] * t;
	w[1] += eta * x[1] * t;
}


void doAllProcess() {
	std::vector<double> w {1, 1, -1};

	std::vector<std::vector<double>> x_set {
		{0, 0}, {0, 1}, {1, 0}, {1, 1}
	};

	std::vector<double> t {
		-1, -1, -1, 1
	};

	std::random_device seed_gen;
	std::mt19937 mt(seed_gen());
	std::uniform_int_distribution<> randint(0, 3);

	for(int i = 0; i < 100; ++i) {
		learning(w, x_set[randint(mt)], t[randint(mt)]);
		if(check(w, x_set, t))
			break;
		std::cout << check(w, x_set, t) << " " << w[0] << "  "
				<< w[1] << "  " << w[2] << "\n" << std::endl;
	}

	for(int i = 0; i < 4; ++i)
		std::cout << judge(w, x_set[i]) << std::endl;
}

int main() {
	doAllProcess();

	return 0;
}

