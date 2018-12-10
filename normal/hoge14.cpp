#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <iterator>

class Neuron {
public:
	Neuron(const std::map<int,double>& w) {
		w_ = w;
	};

	~MacCullochPitts() = default;

	// Receive signals and check firing.
	int isFire(const std::vector<double>& input) {
		double sum = 0.0;

		for(std::size_t i = 1; i < input.size(); ++i)
			sum += input[i] * w[i];

		value = sum;

		return (status = activateFunction(sum - input[0]);)
	}

	// Heaviside function.
	int activateFunction(double n) {
		return n > 0 ? 1 : 0;
	}

	std::vector<double>& getW() noexcept const {
		return w_;
	}

	int getStatus() noexcept const {
		return status_;
	}

	double getValue() noexcept const {
		return value_;
	}

private:
	std::map<int, double> w_;
	int status_;
	double value_;	
};


// Neural Network
class SingleLayerPerceptron {
public:
	SingleLayerPerceptron() {
		input_nuerons = array<MacCullochPitts, 2> { MacCullochPitts(1), MacCullochPitts(1) };
		output_nuerons = array<MacCullochPitts, 1> { MacCullochPitts(2) };
	};

	~SingleLayerPerceptron() = default;

	int propagate(int n1, int n2) {
		input_neurons[0].isFire(std::vector<double>{n1});
		input_neurons[1].isFire(std::vector<double>{n2});

		output_neurons[0].isFire(std::vector<double>{ input_neurons[0].getStatus(),
														input_neurons[1].getStatus() });
	}

	void updateWeight(int correct) {
		auto w_current = output_neurons[0];



	}
	
	void showResult(const std::string& pre) {
		std::cout << output_neurons[0].getStatus() << std::endl;
	}

private:
	array<MacCullochPitts, 2> input_neurons;
	array<MacCullochPitts, 1> output_neurons;
	// Learning coefficient.
	double eta = 0.02;
};

/*
int main() {
	using namespace std;
	array<array<double,1>,2> a;

	for(int i = 0; i < a.size(); ++i)
		for(int j = 0; j < a[0].size(); ++j)
			a[i][j] = i+j;

	cout << a[1][0] << endl;

	return 0;
}

