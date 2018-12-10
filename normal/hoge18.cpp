#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

auto main() -> int {
	plt::plot({1,3,2,4});
	plt::show();
	return 0;
}

