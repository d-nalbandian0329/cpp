#include <iostream>

template <class Strategy>
struct owenership {
	typedef Strategy type;
};

struct reference_count {};
struct deep_copy 	   {};


// Is this type multi-thread-safe or not?
template <bool IsMultiThread>
struct multi_thread {
	static const bool value = IsMultiThread;
};


// Judge that the type is policy or not.
template <class>
struct is_ownership_policy;


template <class>
struct is_multi_thread_policy;



// Smart pointer class must present that
// the template parameter need to be specify or not.

// To implement "Named Template Parameter",
// we must implement following metafunction
// getting required policy from variadic template.

// get_required_arg : Get required policy class from policy list.
// get_optioanl_arg : Get optional policy class from policy list.

template <class... Args>
struct smart_ptr {
	typedef typename
		get_required_arg<
			is_owenership_policy,
			Args...
		>::type
	ownership_policy;

	typedef typename
		get_optional_arg<
			is_multi_thread_policy,
			Args...
		>::type
	multi_thread_policy;
};


