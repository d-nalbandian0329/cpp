#include <iostream>
#include <exception>


/*
RAII(Resource Acquisition Is Initialization)
資源の獲得時に初期化を行う
初期化処理をコンストラクタ内に記述し, 解放処理をデストラクタに記述する
*/

namespace n1 {
	// @ 例外(Exception)
	// if文でエラー処理を行う上での問題
	// 1. 関数内で起きたエラー情報を返しても, 呼び出し元が受け取るとは限らない
	// 2. 関数が返す情報は成功・失敗だけではないためエラー処理と通常の処理の
	//    分岐が区別がつけづらいことがある
	// 3. 関数呼び出しの階層は深くなることがある, その際に呼び出し元まで
	//    エラー情報を伝播させるのは大変

	/*
	try{
		throw 送出する例外オブジェクト
	}
	catch(補足するオブジェクトの型) {

	}

	例外の送出が行われるコードの範囲をtryブロックで囲む
	catchブロックは複数あってもよい, またcatchブロックは
	例外が送出されない限り実行されることはない

	catchキーワードの直後には補足対象となる型が記述してある
	送出された例外オブジェクトと補足対象として指定した型が
	一致した場合, catchブロック内のコードの実行が始まる

	catchブロックの末尾まで実行を終えたら今回の例外に対する
	処理は完了となり, catchブロックを抜けた先から実行が再開される

	catchキーワードに指定された型と例外オブジェクトの型が一致しない場合
	そのcatchブロックでは補足されず, 次のcatchブロックへジャンプする

	現在の関数内のcatchブロックがなくなったらそのまま呼び出し元の関数に
	巻き戻り, 引き続きcatchブロックを探し続ける
	大元の関数へ巻き戻っても例外が補足されなかった場合はstd::terminate関数
	が呼び出される

	std::terminate
	default : std::abort関数を使ってプログラムを異常終了させる
	(動作の変更も可能)
	*/

	int divide(int a, int b) {
		if(b == 0)
		 	throw "ゼロ除算が発生しました";
		return a / b;
	}

	void test() {
		try {
			int result = divide(10, 0);
			std::cout << "result : " << result << std::endl;
		}
		catch(const char* message) {
			std::cout << message << std::endl;
		}

		std::cout << "プログラムを終了します" << std::endl;
	}
}


namespace n2 {
	int divide(int a, int b) {
		if(b == 0)
			throw "DivideByZeroExceprion";
		return a / b;
	}


	class Integer {
	public:
		Integer() : ip(new int()) {
		}

		Integer(int value) : ip(new int(value)) {
		}

		~Integer() { delete ip; }

		const int get() { return *ip; }

		void set(int value) { *ip = value; }

	private:
		int* ip;
	};


	void test() {
		try {
			// RAIIの考え方には沿っているけど面倒
			// スマートポインタを使うべき
			Integer result;

			result.set(divide(10, 0));

			std::cout << "Result : " << result.get() << std::endl;
		}
		catch(const char* msg) {
			std::cout << msg << std::endl;
		}
	}
}


namespace n3 {
// 補足対象クラスに基底クラスを指定しておくと派生クラスの
// 例外が送出されても補足できる
// ＊slicingを避けるために例外を基底クラスで受け取る場合は
//   参照で受け取ること!!

// slicing : 派生クラスの実体を基底クラスへコピーすることで
//           派生クラスに固有の情報が失われること
// pointer, referenceを利用することで避けることが可能


	class my_exception : public std::exception {
	public:
		const char* what() const noexcept override {
			return "This is My Exception Class.";
		}
	};


	void test() {
		try {
			throw my_exception();
		}
		catch(std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
		// 上のcatchで捕捉されなかったそれ以外の例外オブジェクトを捕捉
		// 名前をつけていないため例外オブジェクトへアクセスできない
		// ある例外が送出されている状態で単に throw; と記述すると同じ
		// 例外をそのままもう一度送出できる
		//catch(...) {
		//
		//}
	}
}


namespace n4 {
// tryブロックで対応できないもの
// クラスのメンバ変数を初期化する際に送出された例外
// 基底クラスのコンストラクタから送出された例外
// => 関数tryブロックを利用する

/*
	class Derived : public Base {
	public:
		Derived()
		try
		 : Base(100),
			m_other(200) {
		}
		catch() {
		}

	private:
		Other m_other;
	}
*/

// コンストラクタで例外が発生する
// コンストラクタの実装の末尾まで処理が終わっていないため
// 今インスタンス化しようとしていたオブジェクトは作られていない
// オブジェクトが作られていないためデストラクタも呼ばれない
//
// コンストラクタが途中まで実行されているため明示的に解放処理が
// 必要なものを作ってしまっている可能性もある
//
// 

	class divide_by_zero_exception : public std::exception {
	public:
		const char* what() const noexcept override {
			return "Divide by zero exception.";
		}
	};

	int divide(int a, int b) {
		if(b == 0)
			throw divide_by_zero_exception();

		return a / b;
	}


	class MyClass {
	public:
		MyClass()
			try
			: value_(new int(divide(10,0))) {	
				std::cout << "constructor top" << std::endl;
				std::cout << "constructor bottom" << std::endl;
			}
			catch(std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}

		~MyClass() {	
			std::cout << "destructor top" << std::endl;

			delete value_;

			std::cout << "destructor bottom" << std::endl;
		}

	private:
		int* value_ = nullptr;
	};


	void test() {
		MyClass obj;
	}

}



int main() {
//	n1::test();
//	n2::test();
//	n3::test();
	n4::test();
}

