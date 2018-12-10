#include "ceres/ceres.h"
#include "glog/logging.h" 

using ceres::AutoDiffCostFunction;
using ceres::CostFunction;
using ceres::Problem;
using ceres::Solver;
using ceres::Solve;


struct CostFunctor {
	template <class T>
	bool operator()(const T* x, T* residual) const {
		residual[0] = T(10.0) - x[0];
		return true;
	}
};


int main(int argc, char** argv) {
	google::InitGoogleLogging(argv[0]);

	// 初期値
	double initial_x = 5.0;
	double x = initial_x;

	Problem problem;

	CostFunction* cost_function
		= new AutoDiffCostFunction<CostFunctor,1,1>(new CostFunctor);

	problem.AddResidualBlock(cost_function, NULL, &x);

	Solver::Options options;

	options.linear_solver_type = ceres::DENSE_QR;
	options.minimizer_progress_to_stdout = true;
	Solver::Summary summary;
	Solve(options, &problem, &summary);

	std::cout << summary.BriefReport() << std::endl;
	std::cout << "x : " << initial_x << " -> " << x << std::endl;

	return 0;
}

