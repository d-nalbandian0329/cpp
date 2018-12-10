#include <iostream>
#include <string>

template <class T>
class Stack {
private:
	T* data_;
	int index_;
	int capacity_;

public:
 
	explicit Stack(int n) : capacity_(n), index_(0) {
		data_ = new T[capacity_];
	}

	~Stack(){
		delete[] data_;
	}

	void push(T x){
		if(index_ < capacity_)
			data_[index_++] = x;
	}

	T top() const {
		return data_[index_-1];
	}

	void pop(){
		if(index_ > 0)
			--index_;
	}
};

int main(){
	using namespace std;

	Stack<int> istack(5);
	Stack<long> lstack(8);
	Stack<void*> pstack(3);

	istack.push(1);
	lstack.push(2);
	int hoge = 3;
	pstack.push(&hoge);

	cout << istack.top() << endl;
	cout << lstack.top() << endl;
	cout << *(static_cast<int*>(pstack.top())) << endl;

	return 0;
}

// explicit付きで宣言されたコンストラクタは初期化と明示的な
// 型変換だけに利用される.
// 通常, 単一の実引数でコンストラクタが起動されると
// コンストラクタはその実引数の型からクラスの型へと暗黙的に
// 型変換を行うかのように振る舞う
// それなりの理由がない場合, 単一の引数を受け取るコンストラクタには
// explicitをつけるべき
/*
// explicitをつけて宣言したコンストラクタの定義をクラス外で行う場合は
// explicitを外す
class Date {
	int d, m, y;

public:
	explicit Date(int dd);
...
};

// これはエラー
explicit Date::Date(int dd){ ... }

=による初期化はコピー初期化とみなされる

通常, 初期化されるオブジェクトは初期化子のこぴーを持つが
初期化子が右辺値の場合は最適化によってコピー演算の代わりに
ムーブ演算が実行されることもある

=を記述しない場合は明示的な初期化となる => 直接初期化
struct X {
	explicit X();
	explicit X(int,int);
};

// エラー, コピー初期化は暗黙的な初期化
X x1 = {};
X x2 = {1, 2};

// おk, 直接初期化は明示的な初期化
X x3 {};
X x4 {1, 2};

int f(X);

// エラー, 暗黙的
int x5 = f({});
int x6 = f({1,2});

// おk, 明示的
int x7 = f(X{});
int x8 = f(X{1,2});








*/

