#include <iostream>

template <class T>
class Point {
	// Point<任意の型>がPoint<T>のfriendであることを意味する
	// つまり, Point<T>がPoint<任意の型>のprivateメンバにアクセスできる
	template<class> friend class Point;

private:
    T x_; 
    T y_; 

public:
	// Constructor template
	template <class U>
	Point(const Point<U>& r) : x_(r.x_), y_(r.y_){
	}

    Point(T x = T(), T y = T()) : x_(x), y_(y) {
    }   

    Point(const Point& pt) : x_(pt.x_), y_(pt.y_){
    }   

    void print(std::ostream& s) const {
        return s << '(' << x_ << ',' << y_ << ')' << '\n';
    }   
};

int main(){
	Point<int> ip(12, 34);

	// ここでコンストラクタテンプレートが動いてくれる
	// Point<long>::Point<long>(const Point<int>&)
	Point<long> lp(ip);


	return 0;
}

