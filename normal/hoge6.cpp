#include <iostream>
#include <stdexcept>


class Array {
private:
	int data[10][10][10];

public:
	Array() {
		for(int i = 0; i < 10; ++i)
			for(int j = 0; j < 10; ++j)
				for(int k = 0; k < 10; ++k)
					data[i][j][k] = i*10 + j*10 + k;
	}

	~Array() = default;

	int& operator[](std::initializer_list<int> list) {
		if(list.size() != 3)
			throw std::invalid_argument("OutOfBoundException");

		auto ite = list.begin();
		int const x = *ite; ++ite;
		int const y = *ite; ++ite;
		int const z = *ite;

		return data[x][y][z];
	}
};


auto main() -> int {
	Array foo;

	try{
		std::cout << foo[{1,1,1}] << std::endl;
	}
	catch(const std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}

