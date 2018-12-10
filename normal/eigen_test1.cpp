#include <iostream>
#include <Eigen/Core>
#include <Eigen/LU>


void doAllProcess() {
	Eigen::Matrix2f A;

	A << 1,2,
		 3,4;

	std::cout << "A :\n" << A << std::endl;
	std::cout << "A^-1 :\n" << A.inverse() << std::endl;
	std::cout << "A * A^-1 :\n" << A*A.inverse() << std::endl;
}

auto main() -> int {
	doAllProcess();

	return 0;
}

