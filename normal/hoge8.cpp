#include <iostream>

class Point {
public:
	Point() {
		x = y = z = 0.0;
	}

	Point(double x, double y = 0.0, double z = 0.0) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Point(const Point& other) = default;


	void print() const {
		std::cout << "x : " << this->x << std::endl;
		std::cout << "y : " << this->y << std::endl;
		std::cout << "z : " << this->z << std::endl;
	}

	inline double getX() const { return this->x; }
	inline double getY() const { return this->y; }
	inline double getZ() const { return this->z; }
	inline double* getPoints() { return this->coordinates; }

private:
	union {
		double coordinates[3];
		double x, y, z;
	};
};






// trailing return type syntax
auto main() -> int {
	Point fuga(1,2,3);
	Point hoge = fuga;

	hoge.print();
	fuga.print();
}

