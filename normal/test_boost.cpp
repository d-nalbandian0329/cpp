#include <iostream>
#include <string>
#include <boost/format.hpp>


int main() {
	std::cout << (boost::format("%d, %d") % 1 % 2).str(); << std::endl;
}

