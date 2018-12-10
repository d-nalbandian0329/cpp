#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <numeric>

class Hypothesis {
public:
	virtual ~Hypothesis() = default;
	virtual double h(const std::vector<double>&) = 0;
};



class LinearHypothesis : public Hypothesis {
public:
	LinearHypothesis() = default;

	~LinearHypothesis() = default;

	LinearHypothesis(const std::vector<double>& theta)
		: theta_(theta) {
	}

	LinearHypothesis(std::vector<double>&& theta)
		: theta_(std::move(theta)) {
	}

	double h(const std::vector<double>& input) override {
		return std::inner_product(std::begin(input), std::end(input),
									std::begin(theta_), 0.0);
	}

	std::vector<double> theta_;
};


class CostFunction {
public:
	virtual ~CostFunction() = default;

	virtual double j(const std::vector<double>& input,
						const std::vector<double>& t) = 0;

	virtual double del_j(const std::vector<double>& input,
							const std::vector<double>& t) = 0;

	std::unique_ptr<Hypothesis> hypothesis_;
};


class MeanSquaredError : public CostFunction {
public:
	MeanSquaredError(std::unique_ptr<Hypothesis>&& hypothesis)
		: hypothesis_(std::move(hypothesis)) {
	}


	// Calculate cost.
	double j(const std::vector<double>& input,
				const std::vector<double>& t) override {

		double score = 0.0;
		int i = 0;
		for(auto ite_x = std::begin(input), ite_t = std::begin(t);
				ite_x != std::end(input); ++ite_x, ++ite_t) {
			score += (std::pow(hypothesis_->h(*ite_x) - *ite_t, 2) - score) / ++i;
		}

		return score / (2 * input.size());
	}

	// 
	std::vector<double> del_j(const std::vector<double>& input,
								const std::vector<double>& t) override {
		std::vector<double> ret((hypothesis_->theta).size());

		for(int i = 0; i < ret.size(); ++i) {
			double theta_k = 0.0;
			for(int j = 0; j < input.size(); ++j) {


}_?			}
		}

	}

	std::unique_ptr<Hypothesis> hypothesis_;
};






auto main() -> int {
	std::vector<double> theta {1, 1};

	std::unique_ptr<Hypothesis> hypothesis(new LinearHypothesis(theta));

}

