// Implementation of enable_if.
#include <iostream>
#include <type_traits>


// 定数真偽値を受け取るメタ関数
template <bool B, class T = void>
struct enable_if_c {
	typedef T type;
};

// falseを受け取った場合の明示的特殊化
template <class T>
struct enable_if_c<false, T> {};


// インターフェース部分
template <class Cond, class T = void>
struct enable_if : public enable_if_c<Cond::value, T> {};


template <bool B, class T = void>
struct disable_if_c {
	typedef T type;
};

template <class T>
struct disable_if_c<true,T> {};


template <class Cond, class T = void>
class disable_if : public disable_if_c<Cond::value, T>{};


struct is_class_impl {
	// paraemter is a pointer to member function.
	template <class T>
	static auto check(void (T::*)()) -> std::true_type;

	template <class T>
	static auto check(...) -> std::false_type;
};


template <class T>
class is_class : public decltype(is_class_impl::check<T>(nullptr)) {};


template <class T>
void check(T value,
			typename enable_if<is_class<T>>::type* = nullptr){
	std::cout << "T is a class.\n";
}


template <class T>
void check(T value,
			typename disable_if<is_class<T>>::type* = nullptr) {
	std::cout << "T isn't a class.\n";
}


auto main() -> int {

}

