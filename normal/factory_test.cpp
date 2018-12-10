#include <iostream>
#include <algorithm>
#include <memory>
#include <string>
#include <type_traits>

struct Magica {
	virtual std::string call() const = 0;
};

struct Homura : Magica {
	std::string call() const { return "ﾏﾄﾞｶｧ!"; }
};

struct Madoka : Magica {
	std::string call() const { return "ﾎﾑﾗﾁｬﾝ!"; }
};


// enable_if<b,X>
// b == true ならばX そうでない場合, ::typeというメンバは存在せず
// ほとんどの場合、置換失敗となる

/*
namespace std {
	template <class Base, class Derived>
	struct is_base_of;

	// C++17
	template <class Base, class Derived>
	constexpr bool is_base_of_v = is_base_of<Base,Derived>::type;
}

概要：型Baseが型Derivedの基底クラスか調べる

要件：BaseとDerivedが非共用体のクラスであり異なる型である場合
      (cv修飾は無視される)、Derivedは完全型でなければならない

効果：is_base_of は 型Baseが型Derivedの基底クラス
	  (cv修飾は無視される)である、もしくは2つが同じ
　　　クラス型ならばtrue_typeから派生し、そうでなければ
　　　false_typeから派生する

備考：は政治のprivate, protected指定は派生関係の判定に影響しない

*/

struct Incubator {
	template <
		class T,
		class C = typename std::enable_if<std::is_base_of<Magica,T>::value>::type
	>
	static std::unique_ptr<Magica> create() {
		return std::unique_ptr<Magica>{ new T{} };
	}
};

auto main() -> int {
	const auto girls =
		{ Incubator::create<Madoka>(), Incubator::create<Homura>() };

	std::for_each(girls.begin(), girls.end(),
					[](const std::unique_ptr<Magica>& girl){
						std::cout << (*girl).call() << std::endl;
					}
	);

	return 0;
}

