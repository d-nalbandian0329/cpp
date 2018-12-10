extern "C" {
#include "hoge.h"
}

#include <iostream>

void hoge(int n) {
	std::cout << "cpp func : " << n << std::endl;
}

int main() {
	hoge();
	hoge(10);
}

