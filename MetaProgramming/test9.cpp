// http://fimbul.hateblo.jp/entry/2013/07/20/040237
// index_tuple idiom
// idnex_tuple<0,1,2,3>のように連番の整数値を型リストとして
// もつオブジェクトを生成するイディオム

#include <type_traits>

template <std::size_t... indexes>
struct index_tuple;


template <std::size_t first, std::size_t last,
			class result = index_tuple<>, bool flag = first >= last>
struct index_range {
	using type = result;
};

template <std::size_t step, std::size_t last, std::size_t... indexes>
struct index_range <step, last, index_tuple<indexes...>, false>
		: index_range<step+1, last, index_tuple<indexes...,step>>{
};


auto main() -> int {
	static_assert(std::is_same<
						index_tuple<0,1,2,3,4>,
						index_range<0,5>::type
						>::value, "");


}



