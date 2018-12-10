// http://fimbul.hateblo.jp/entry/2013/07/20/040237
// index_tuple idiom

// index_tuple を生成するためのイディオム
// index_tuple : 連番の整数値を型リストとしてもつオブジェクト
// ex.) index_tuple<0,1,2,3>
// O(n) order

#include <iostream>
#include <array>
#include <type_traits>

namespace my {
/*
	template <std::size_t... indices>
	struct index_tuple;

	template <std::size_t... indices, std::size_t x, std::size_t end>
	struct index_tuple {
		using type
			= (x < end-1
				? index_tuple<indices..., index_tuple<x, x+1, end>::type>
				: index_tuple<indices..., x>
			);
	};

	template <std::size_t start, std::size_t end>
	class index_range <start, end> {
		using type = index_tuple<start, start + 1, end>::type;
	};
*/

	template <class T, std::size_t N, std::size_t... numbers>
	auto makeSeqArray() -> std::array<T, N> {
		return std::move(std::array<T, N> {{ numbers... }});
	}

	template <class T, std::size_t N>
	auto print(const std::array<T,N>& ary) -> void {
		std::cout << "data :";
		for(auto&& e : ary)
			std::cout << " " << e;
		std::cout << std::endl;
	}

	// template parameter に受け取った数値の総和をコンパイル時に算出する
	template <std::size_t head, std::size_t... remain> 
	struct compile_sum_impl  {
		static constexpr std::size_t value = head + compile_sum_impl<remain...>::value;
	};

	template <std::size_t N>
	struct compile_sum_impl <N> {
		static constexpr std::size_t value = N;
	};

	template <std::size_t... indices>
	struct compile_sum : public compile_sum_impl <indices...> {
	};
}


int main() {
	auto&& ret = my::makeSeqArray<int,5,0,1,2,3,4>();

	my::print(ret);

	//std::cout << my::compile_sum<0,1,2,3,4>::value << std::endl;
}

