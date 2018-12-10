#include <iostream>
#include <string>

template <class T>
class Util {
private:
	T value_;

public:
	Util(const T& v);
	void add(const T& v);
	T get() const;
	int size() const;
};

template <class T>
Util<T>::Util(const T& v) : value_(v) {}

template <class T>
void Util<T>::add(const T& v){
	value_ += v;
}

template <class T>
T Util<T>::get() const { return value_; }

// value_がメンバ関数size()を持っていること前提のコード
// しかし, 実際にテンプレート引数にint型を与えて
// インスタンス化してもコンパイルできてしまう
// これはsize()関数が呼び出されるまでインスタンス化が行われないため
// => これを回避したい場合は明示的インスタンス化を行う
//
// template class Util<int>;
//
// こうすると全てのメンバ関数がインスタンス化されるので
// size()関数の部分でコンパイルエラーを発生させられる
//
// また, 各メンバ関数を明示的インスタンス化する場合は
// template void Util<int>::add(const T& v);
// と記述する

template <class T>
int Util<T>::size() const { return value_.size(); }


// 明示的インスタンス化によって型Tがメンバ関数size()
// を持たない場合はコンパイルエラーが発生する
// template class Util<int>;

int main(){
	Util<int> iu(12);
	iu.add(31);
	std::cout << iu.get() << std::endl;

	Util<std::string> su("Hello,");
	su.add("world!");
	std::cout << su.get() << std::endl;

	return 0;
}

