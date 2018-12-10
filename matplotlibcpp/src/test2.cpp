#include "../header/matplotlibcpp.h"
#include <cmath>

namespace plt = matplotlibcpp;

using namespace std;


void prepareData(vector<double>&x, vector<double>& y, vector<double>& z, const int n) {
	x.resize(n);
	y.resize(n);
	z.resize(n);

	for(int i = 0; i < n; ++i) {
		x.at(i) = i * i;
		y.at(i) = sin(2 * M_PI * i / 360.0);
		z.at(i) = log(i);
	}

}

void doAllProcess() {
	vector<double> x, y, z;
	constexpr int n = 5000;

	prepareData(x, y, z, n);

	//plt::figure_size(1200, 780);

	plt::plot(x, y);

	vector<double> w(n,2);
	plt::plot(x, w, "r--");

	plt::named_plot("log(x)", x, z);

	plt::xlim(0, 1000*1000);

	plt::legend();

	plt::save("../figure/basic.png");
}


auto main() -> int {
	doAllProcess();

	return 0;
}

