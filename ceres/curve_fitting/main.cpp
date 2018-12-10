#include "ceres/ceres.h"
#include "glog/logging.h"
#include <cmath>
#include <vector>

using namespace std;

using ceres::AutoDiffCostFunction;
using ceres::CostFunction;
using ceres::Problem;
using ceres::Solver;
using ceres::Solve;

vector<double> x={
    0.0,
    0.1,
    0.2,
    0.3,
    0.4,
    0.5,
    0.6,
    0.7,
    0.8,
    0.9,
    1.0,
    1.1,
    1.2,
    1.3,
    1.4,
    1.5,
    1.6,
    1.7,
    1.8,
    1.9,
    2.0,
    2.1,
    2.2,
    2.3,
    2.4,
    2.5,
    2.6,
    2.7,
    2.8,
    2.9,
    3.0,
    3.1,
    3.2,
    3.3,
    3.4,
    3.5,
    3.6,
    3.7,
    3.8,
    3.9,
    4.0,
    4.1,
    4.2,
    4.3,
    4.4,
    4.5,
    4.6,
    4.7,
    4.8,
    4.9,
    5.0,
    5.1,
    5.2,
    5.3,
    5.4,
    5.5,
    5.6,
    5.7,
    5.8,
    5.9,
    6.0,
    6.1,
    6.2,
    6.3,
    6.4,
    6.5,
    6.6,
    6.7,
    6.8,
    6.9,
    7.0,
    7.1,
    7.2,
    7.3,
    7.4,
    7.5,
    7.6,
    7.7,
    7.8,
    7.9,
    8.0,
    8.1,
    8.2,
    8.3,
    8.4,
    8.5,
    8.6,
    8.7,
    8.8,
    8.9,
    9.0,
    9.1,
    9.2,
    9.3,
    9.4,
    9.5,
    9.6,
    9.7,
    9.8,
    9.9
};

vector<double> y={
    1.02490416236 ,
    1.29305791957 ,
    1.21808052029 ,
    1.3588488308  ,
    1.39714914507 ,
    1.21248581892 ,
    1.43837677213 ,
    1.70810328393 ,
    1.23257688353 ,
    1.01403219676 ,
    1.50925801818 ,
    1.6662848504  ,
    1.62685479195 ,
    1.72943981083 ,
    1.6268189861  ,
    1.5232015196  ,
    1.75886813965 ,
    1.93519928417 ,
    1.9708652989  ,
    2.34153642459 ,
    2.33431720324 ,
    2.19900176974 ,
    2.41857038053 ,
    2.05907010769 ,
    2.14753269599 ,
    2.26971851294 ,
    2.67786409035 ,
    2.36423267435 ,
    2.98507375854 ,
    2.61935149386 ,
    2.61920129111 ,
    2.77018486544 ,
    2.58031060219 ,
    3.39765031555 ,
    3.00758588694 ,
    3.03219044437 ,
    3.47396275685 ,
    3.33445068721 ,
    3.35104422442 ,
    3.66884606242 ,
    3.76938172337 ,
    3.71002906934 ,
    3.99279950267 ,
    4.02309903921 ,
    4.48927062765 ,
    3.99157533677 ,
    4.39760556415 ,
    4.58161866676 ,
    4.17123107607 ,
    4.72860665359 ,
    5.098285443   ,
    4.92916651281 ,
    5.30439889148 ,
    5.56271822085 ,
    5.78117714742 ,
    5.74989797305 ,
    5.72580355915 ,
    5.67394357099 ,
    6.53751089972 ,
    6.52964092617 ,
    6.17575247141 ,
    6.66194065898 ,
    7.10096705189 ,
    7.13447829695 ,
    7.76971839588 ,
    8.12613000585 ,
    7.62828689202 ,
    8.38091275525 ,
    8.67785948187 ,
    8.36503603111 ,
    9.45888208319 ,
    9.34159256258 ,
    9.56090107074 ,
    9.8416453843  ,
    9.97227446831 ,
    10.1873938121 ,
    10.8344553317 ,
    11.0763825902 ,
    11.2842012655 ,
    11.9209145172 ,
    12.0536165764 ,
    12.5759989771 ,
    13.1364781742 ,
    13.3973702715 ,
    13.6533113094 ,
    14.3127362678 ,
    14.5541054308 ,
    15.0865724847 ,
    15.3825751    ,
    15.7758082945 ,
    16.218452986  ,
    16.9454721082 ,
    17.223654526  ,
    18.079015446  ,
    18.7208248424 ,
    19.4461197524 ,
    19.6863469253 ,
    20.4498195898 ,
    21.1118474511 ,
    21.4684135588 
};



struct ExponentialResidual {
	ExponentialResidual(double x, double y)
		: x_(x), y_(y){}

	template <class T>
	bool operator()(const T* m, const T* c, T* rasidual) const {
		rasidual[0] = T(y_) - exp(T(x_) * m[0] + c[0]);
		return true;
	}

private:
	const double x_;
	const double y_;
};


int main(int argc, char** argv) {
	google::InitGoogleLogging(argv[0]);

	// target function : e^(mx + c)
	double m = 0.0;
	double c = 0.0;

	Problem problem;

	for(int i = 0; i < x.size(); ++i) {
		CostFunction* cost_function
			= new AutoDiffCostFunction<ExponentialResidual,1,1,1>(new ExponentialResidual(x[i],y[i]));
		problem.AddResidualBlock(cost_function, NULL, &m, &c);
	}

	// 最適化のオプション設定用構造体
	Solver::Options options;
	options.linear_solver_type = ceres::DENSE_QR;
	// 最適化の結果を標準出力へ出力
	options.minimizer_progress_to_stdout = true;

	// 最適化の結果を格納する構造体
	Solver::Summary summary;

	// execute optimization
	Solve(options, &problem, &summary);

	std::cout << summary.BriefReport() << std::endl;
	std::cout << "m : " << m << ", c : " << c << std::endl;

	return 0;
}

