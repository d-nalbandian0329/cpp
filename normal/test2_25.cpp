#include <iostream>
#include <vector>

template <int... List>
std::vector<int> initializer() {
	std::vector<int> v = { List... };
	return v;
}

int main() {
	std::vector<int> v = initializer<1,2,3>();

	for(int x : v)  std::cout << " " << x;
	std::cout << std::endl;
}

