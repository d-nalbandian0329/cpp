#include <iostream>

struct not_found {};

// This primary template is for finding target policy class.
// This uses higher-order metafunction to judge that
// Head is target-policy-class or not.
// Otherwise recursively call find_if_impl with predication and remained type list.
template <template <class> class Pred, class Head, class... Tail>
struct find_if_impl {
	typedef typename
		std::conditional<
			Pred<Head>::value,
			Head,
			typename find_if_impl<Pred,Tail...>::type
		>::type
	type;
};


template <template <class> class Pred, class Head>
struct find_if_impl <Pred, Head> {
	typedef typename
		std::conditional<
			Pred<Head>::value,
			Head,
			not_found
		>::type
	type;
};


// If variadic parameter is empty,
// return not_found
//template <template <class> class Pred>
//struct find_if_impl <Pred> {
//	typedef not_found type;
//};


// Interface.
template <template <class> class Pred, class... List>
struct find_if {
	typedef typename find_if_impl<Pred, List...>::type type;
};


template <template <class> class Pred, class... List>
struct get_required_arg {
	typedef typename find_if<Pred, List...>::type type;
	static_assert(!std::is_same<type, not_found>::value,
					"required policy not found");
};

template <class Opt, template <class> class Pred,
			class... List>
struct get_optional_arg {
private:
	typedef typename find_if<Pred, List...>::type result;

public:
	typedef typename
		std::conditional<
			!std::is_same<result, not_found>::value
			result,
			Opt
		>::type
	type;
};


template <class Strategy>
struct ownership {
	typedef Strategy type;
};

struct reference_count {};
struct deep_copy {};

template <bool IsMultiThread>
struct multi_thread {
	static const bool value = IsMultiThread;
};

template <class>
struct is_ownership_policy {
	static const bool value = false;
};

template <class Strategy>
struct is_ownership_policy<ownership<Strategy>> {
	static const bool value = true;
};

template <class>
struct is_multi_thread_policy {
	static const bool value = false;
};

template <bool IsMultiThread>
struct is_multi_thread_policy<multi_thread<IsMultiThread>> {
	static const bool value = true;
};

template <class... Args>
struct smart_ptr {
	typedef typename
		get_required_policy<
			is_ownership_policy,
			Args...
		>::type
	type;

	typedef typename
		get_optional_policy<
			is_multi_thread_policy,
			Args...
		>::type
	type;
};







