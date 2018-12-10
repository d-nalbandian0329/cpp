#include <iostream>
#include <tuple>

// パラメータパックには0個以上の要素が含まれる
// 参考ページではinitializer_listの中に値を展開して
// 戻り値として返しているけどブレースで括られてる値
// が全部異なる型だからcompile errorになって当然では？？
// => C++14 でコンパイルしたら通っちゃった
namespace my{
	template <class ...Args>
	auto make_tuple(Args ...args) -> std::tuple<Args...> {
		//return std::tuple<Args...> { args... };	// pack expansion
		return std::tuple<Args...> { args... };	// pack expansion
	}

	void test() {
		// std::tuple<unsigned long long, int, float, double>
		auto ret = my::make_tuple(1ull, 1, 1.0f, 1.0);

		std::cout << std::get<0>(ret) << std::endl;
		std::cout << std::get<1>(ret) << std::endl;
		std::cout << std::get<2>(ret) << std::endl;
		std::cout << std::get<3>(ret) << std::endl;
	}

}


namespace test1 {
	struct X {
		int ary[3];
		X() : ary {10, 20, 30} {}
	};

	void test() {
		X x;
		std::cout << x.ary[0] << " " << x.ary[1] << " " << x.ary[2] << std::endl;
	}

}


namespace test2 {
	template <class T>
	class Hoge {
		void f() {
			T::get();
		}
		void g();
	};

	void test() {
		// 使用されないメンバ関数はインスタンス化されないから
		// 気づきにくいエラーのもと
		Hoge<int> int_h {};
	}
}




auto main() -> int {
	/*
	{
		using namespace my;
		test();
	}
	*/

	/*
	{
		using namespace test1;
		test();
	}
	*/

	{
		using namespace test2;
		test();
	}
}

