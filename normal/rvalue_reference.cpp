// ざっくり言うと
// lvalue : 明示的に実体のある名前付きオブジェクト
// rvalue : 一時的に生成される無名オブジェクト

// C言語の時には単純に代入演算子の左右どちらか
// だったので右辺地, 左辺値という訳でも問題なかった

// C++ ではそういう場合のみではないらしい


/*
struct X {};

int f() { return 0; }


int main() {
	int i = 0;	// lvalue

	i;			// lvalue
	0;			// rvalue, temporary object

	X x;

	x;			// lvalue
	X();		// rvalue

	f();		// rvalue
}
*/


// lvalueをrvalueに変換することはできるがその逆は不可
// C++98のreference => lvalue reference



/*
struct X {};

void f(X &){ }
void g(X const &) {}

int main() {
	X x;

	f(x);

// VC++の独自拡張(/Zaで無効にできる)ではこいつのコンパイルが通ってしまう
//	f(X());  // Errro

	g(X());  // const lvalue reference can reference rvalue!
}
*/


// rvalue reference
// => rvalueに対する参照

/*
struct X {};

int main() {
	X x;

	// lvalue reference
	X & lr1 = x;	// OK, x is lvalue.
	//X & lr2 = X();	// Error, X() is rvalue.

	// rvalue reference
	//X && rr1 = x;	// Error, x is lvalue.
	X && rr2 = X();	// OK, X() is rvalue.
}
*/

// rvalue reference の存在意義
// => const lvalue reference でなくても rvalue
//    を参照できるようになっただけでは？

// その通り, const lvalue referenceでなくてもrvalueを参照できるようになるだけ

// rvalueオブジェクト：名前がない, 参照されなくなった時点で破棄される
// => 勝手に破棄されるなら書き換えても無駄じゃないか？
//    constでなくなったのがそんなに嬉しいのか？


// Move Semantics
/*
class X {
public:
	// Defult Constructor
	X() {
		ptr = new char[1000];
		// バッファに対して時間のかかる書き込みを実行
	}

	// Copy Constructor
	X(X const & r){
		ptr = new char[1000];
		std::copy(&ptr[0], &ptr[1000], &r.ptr[0]);
	}

	// Destructor
	~X() {
		delete [] ptr;
	}


private:
	char* ptr;
};
*/

// 上記のクラスにおいて, コンストラクタとコピーコンストラクタの
// 実行速度が遅いのは明らか
// => コピーをポインタの挿げ替えにしてパフォーマンスを向上したい
//    問題点：それをやるとコピー元のオブジェクトが使えなくなってしまう
//            => 二度と使わないものならいいんでないか？
//				 temporary objectとか




/*
struct X {};

X f() { return X(); }

int main() {
	// 関数fの戻り値はrvalue
	X a(f());	// (1)

	// 例えば一時オブジェクトtmpをこれ以降使わないとする
	// そうすると(1)の記述のときと同様, (2)の記述では
	// ポインタの挿げ替えを行って欲しい
	// => どうやってその意図を表現する？？
	//    rvalueにしてやってそのオブジェクトがポインタを横取り
	//	  されても問題ない存在であることを表現する
	X tmp;
	X b(tmp);	// (2)
}
*/


// Move constructor
// 先述の(1)のコピーをポインタの挿げ替えにするためにクラスXに
// rvalue referenceを引数に取るコンストラクタを用意する

/*

X func() { return X(); }

class X {
public:
	char* ptr;

	// Move constructor
	X(X&& r) {
		ptr = r.ptr;
		
		// コピー元のオブジェクトをnullptrにしておかないと
		// デストラクタが走る際にランタイムエラーになってしまう
		r.ptr = nullptr;
	}
};

int main() {
	// Call Move constructor.
	X a(func());


	X tmp;
	// これをMove constructorの呼び出しにしたい場合は
	// どうすればよい？？
	// tmpがこれ以降使われないかどうかをコンパイラは静的に
	// 決定することができない!
	// => プログラマがコンパイラへ意図を伝える必要がある
	// X a_new(tmp);

	// このようにrvalueへキャストしてやればmove constructor
	// を呼び出すことができる
	X b(static_cast<T &&>(tmp));

	// !! 正直 static_cast<T &&>() 打ち込むのが面倒
	// => std::move()
	//    rvalueへのキャストを行う関数

}

*/


/*
// 実装例

namespace std {
	template <class T>
	inline typename std::remove_reference<T>::type&&
	move(T&& t){
		return static_cast<std::remove_reference<T>::type&&>(t);
	}
}

// 自前でキャストを書くとエラーの元なのでstd::moveを使おう

*/

/*

#include <iostream>
#include <typeinfo>

class X {
public:
	X(){
		std::cout << "default constructor" << std::endl;
		ptr = new char[1000];
	}

	X(X const& r){
		std::cout << "copy constructor" << std::endl;
		std::copy(&ptr[0], &ptr[1000], &r.ptr[0]);
	}

	X(X&& r){
		std::cout << "move constructor" << std::endl;
		ptr = r.ptr;
		r.ptr = nullptr;
	}

	X & operator=(X&& r) {
		std::cout << "move substitution operator" << std::endl;
		if(this == &r){
			return *this;
		}

		delete [] ptr;

		ptr = r.ptr;
		r.ptr = nullptr;

		return *this;
	}


	char* ptr;
};


// 賢いコンパイラの場合そもそもコピーコンストラクタも
// moveコンストラクタも呼び出されない可能性がある
// ＊ある種の状況においてはコンパイラは安全かつ静的に
//   オブジェクトをコピーせずに使いまわせることを決定できる
//   例えコンストラクタにサイドエフェクトがあったとしても
//   コンストラクタの呼び出しを省略できる
//   この種の最適化は規格で保証されている

// moveな代入演算子を定義して最適化による省略を防ぐ


auto main() -> int {
	//X a(X());

	//X b(a);

	//X c(static_cast<X &&>(a));

	//X d(std::move(a));

	X tmp;
	X x;

	// movableにしたければmoveコンストラクタの他に
	// move代入演算子も定義するべきである
	x = std::move(tmp);

	return 0;
}

*/


/*
#include <iostream>
#include <typeinfo>

struct X {};

template <class T>
struct is_rvalue_reference {
	static const bool value = false;
};

template <class T>
struct is_rvalue_reference<T&&> {
	static const bool value = true;
};



// trailing return type syntax
auto main() -> int {
	X x;

	std::cout << "x   : " << typeid(x).name() << std::endl;
	std::cout << "X() : " << typeid(X()).name() << std::endl;

	std::cout << "Is X() rvalue? : "
		<< (is_rvalue_reference<decltype(X())>::value ? "true" : "false")
		<< std::endl;;
}
*/


// オーバーロード

// lvalue と rvalue は関数の多重定義解決の際に考慮される


/*
#include <iostream>

struct X {};

void f(X& x){
	std::cout << "lvalue reference" << std::endl;
}

void f(X&& x){
	std::cout << "rvalue reference" << std::endl;
}


// lvalueであるかrvalueであるかはコンパイル時に静的に決定できるから
// 当然こういったこともできる
auto main() -> int {
	X x;
	f(x);
	f(X());
}


*/


// テンプレート関数の引数におけるrvalue referenceのargument deduction

// 以下のコードはコンパイルが通る
#include <iostream>
#include <typeinfo>

struct X {};

template <typename T>
void f(T&& t){
	std::cout << typeid(t).name() << std::endl;
}

int main() {
	X x;
	f(x);		// lvalue reference
	f(X());		// rvalue reference
}

// 規格には特別なルールがありテンプレート引数を
// rvalue reference として関数の引数に使った場合の
// argument deductionでlvalueを渡すとlvalue reference
// となる
// => 上記のコードの場合, f()にlvalue referenceを渡すと
//    TがX&になって続く&&は無視され, lvalue referenceとして
//    扱われる



// Perfect forwarding

// 下の関数テンプレートでコピー処理を行っているが
// 引数がrvalueの場合にはmoveしたい
// => そう上手くは行かない
/*
template <class T>
void f(T&& t) {
	X x(t);
}
*/


/*
struct X {};

template <class T>
void f(T&& t) {
	X x(std::move(t));
	// これ以降, tは使用不可
}

int main() {
	X x;

	f(x);	// lvalue reference

	// これ以降, xは使用不可
}
*/


// 引数がlvalue referenceのときにもstd::moveによって
// オブジェクトが使用不可になってしまう！
// main()側でstd::move()した時だけmoveして欲しい！
// f()側はテンプレートがインスタンス化されるまで
// 引き数の方がlvalue referenceかrvalue referenceか
// わからない

// メタプログラミングでどうにかしてみる 

/*
template <class T>
void f(T&& t) {
	if(std::is_lvalue_reference<T>::value)
		X x(t);
	else
		X x(std::move(t));
}
*/

// 結局関数をオーバーロードして対応するのと同様,
// 引数の数だけメタ関数を用意することになる

// コンストラクタに引数がlvalueのときはlvalueを
// rvalueのときはrvalueを渡せれば問題解決

// 以下のようなキャストを使うと解決する
template <class T>
void f(T&& t) {
	X x(static_cast<T&&>(t));
}

// argument deductionによってtemplate parameterが
// lvalueの場合はTが X& になって続く&& が無視される
// rvalueの場合は当然rvalueになる、、、
// => これでテンプレート引数に渡された関数をそのまま別の関数へ
//    引き渡すことができる

// std::forward()
// => キャストするのは面倒だしエラーの元

/*
template <class T>
void f(T&& t) {
	X x(std::forward<T>(t));
}
*/

// std::forwardの実装例

namespace std {
	template <class T, class U,
		class = typename enable_if<
							(is_lvalue_reference<T>::value
								? is_lvalue_reference<U>::value
								: true) &&
							is_convertible<typename remove_reference<U.::type*,
											typename remove_reference<T>::type*>::value
		>::type>
	inline
	T&& forward(U&& u){
		return static_cast<T&&>(u);
	}
}


// 上記メタプログラムの意味合いとしてはTがlvalue referenceなら
// ・Uもlvalue referenceでなければならない
// ・参照を取り除いた状態でUからTへ変換できなければならない
// である
// 2条件のどちらも満たす場合でなければstd::forward()はoverload resolutionの
// 候補から外される => compile error
// これによって典型的なタイプミスなどによるエラーを防ぐことができる

// std::forward() は関数テンプレートの引数をそのまま他の関数に
//渡す際に用いる => Perfect forwarding



// ＠まとめ
// rvalue referenceは名前の通りrvalueへの参照に過ぎない
// std::move() も std::forward() も単なるキャストに過ぎない

// std::move()    => lvalueをmoveしたいときに使う
// std::forward() => 関数テンプレートの引数をそのまま別の関数へ渡したい時に用いる










