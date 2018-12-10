// is_addable metafunction judge that whether T is addable or not.

#include <iostream>
#include <type_traits>

struct is_addable_impl {
	// If they(T, U) aren't addable, template instatiation will fail.
	// But it's not an error(SFINAE).
	// So the process move to next after deleting this function from
	// overload candidate.
	template <class T, class U>
	static auto check(T*, U*)
		-> decltype(
			std::declval<T>() + std::declval<U>(),
			std::true_type()
		);

	template <class T, class U>
	static auto check(...) -> std::false_type;
};


template <class T, class U>
class is_addable_
	: public decltype(is_addable_impl::check<T,U>(nullptr,nullptr)) {};


class Addable {
public:
	Addable operator+(const Addable&){
		return Addable();
	}

private:
	int n;
};


class X {};


auto main() -> int {
	static_assert(is_addable_<int,int>::value, "Integer isn't addable!");
	static_assert(is_addable_<Addable,Addable>::value, "Addable isn't addable!");

//	X doesn't define add operator, so class X isn't addable and comile error occurs.
//	static_assert(is_addable_<X,X>::value, "X isn't addable!");

	std::cout << std::boolalpha;
	std::cout << "Addable + Addable : "
			  << is_addable_<Addable,Addable>::value << std::endl;

	std::cout << "X + X : "
			  << is_addable_<X,X>::value << std::endl;

	std::cout << "int + double : "
			  << is_addable_<int,double>::value << std::endl;
}

