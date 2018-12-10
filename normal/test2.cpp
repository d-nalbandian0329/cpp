#include <iostream>
#include <thread>

void hello (int num) { std::cout << num << std::endl; }

int main() {
	std::thread th1(&hello, 1);
	std::thread th2(&hello, 2);

	th1.join();
	th2.join();

	return 0;
}

