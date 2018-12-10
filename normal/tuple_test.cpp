#include <iostream>
#include <typeinfo>

template <int N, class... Ts>
struct tuple_data;

// 明示的特殊化によって再帰呼び出しの末端定義
template <int N>
struct tuple_data<N> {};

// [2]
template <int N, class THead, class... TBody>
struct tuple_data<N, THead, TBody...>
	: public tuple_data<N + 1, TBody...> {
	THead value;
};


/*
// [3]
// 最初の呼び出しによって以下のインスタンス化
// struct tuple <char, int, const char*>
// 		: public tuple_data <0, char, int, const char*>{};

tuple_data<0, char, int, const char*>が[2]により
struct tuple_data<0, char, int, const char*>
	: public tuple_data<1, int, const char*>{
	char value;
};

以降
tuple_data<1, int, const char*>
tuple_data<2, const char*>
が再帰的にインスタンス化されていき, 最終的に
tuple_data<3>がインスタンス化されて再帰が完了する
*/

template <class... Ts>
struct tuple : public tuple_data<0, Ts...> {};




template <int N, class THead, class... TBody>
THead& get_tuple_data(tuple_data<N, THead, TBody...>& t) {
	return t.value;
}

template <int N, class... Ts>
auto get(tuple<Ts...>& t) -> decltype(get_tuple_data<N>(t)) {
	return get_tuple_data<N>(t);
}


void printType(){
	std::cout << std::endl;
}

template <class THead, class... TBody>
void printType(THead head, TBody... body){
	std::cout << '(' << typeid(THead).name() << ')' << head;
	if(sizeof...(body) > 0)
		std::cout << ",";
	printType(body...);
}


int main() {
	// インスタンス化 => [3]へ
	tuple<char, int, const char*> t;

	get<0>(t) = 'T';
	get<1>(t) = 4;
	get<2>(t) = "two";

	printType(get<0>(t),get<1>(t),get<2>(t));
}

