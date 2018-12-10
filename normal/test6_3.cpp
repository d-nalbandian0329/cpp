// A policy class used vecry frequently
// should be set to default template parameter.

/*
ex.) Set debug_log policy class to default template parameter.

template <class Policy = debug_log>
struct hoge {
	static void foo() const {
		Policy::print("Fatal Error!");
	}
};


// For convinience, you can use template aliasing or typedef.

using default_hoge = hoge<default_log>;
or
typedef hoge<default_log> default_hoge;

The changeability of policy class enable user to
switch process at compile time.

*/

// ex.) Implementation method of smart pointer.
/*
・参照カウント方式
・ディープコピー方式
・書き込み時コピー方式
・参照リンク方式
・破壊型コピー方式 ... etc

// implementation with inheritance.

class smart_ptr {
	int* ptr;
public:
	virtual ~smart_ptr(){}
};

// Reference count method smart pointer.
class reference_count_ptr : public smart_ptr {};

// Deep copy method smart pointer.
class deep_copy_ptr : public smart_ptr {};

// Copy on write method smart pointer.
class copy_on_write : public smart_ptr {};

But there are problems in this method.

Let's show next example.

next: Think about adding thread safe option
	  to smart pointer.

// Smart pointer with thread safe.
class single_thread_model {.....};
class multi_thread_model  {.....};

// Smart pointer with reference count method and single thread.

class single_thread_reference_count_ptr
	: public reference_count_ptr,
	  public single_thread_model {};

// Smart pointer with reference count method and multi thread.
class multi_thread_reference_count_ptr
	: public reference_count_ptr,
	  public multi_thread_model {};

......

// As decribed above, we use inheritance to explain
// to explain diagonally function combination.

// But in this method, inheritance relationship
// increases exponentially each of adding option.

// If you use policy-based design, only define class template
// even if the class has multi option.

// ex.) Smart poniter of policy-based design.
class single_thread_model { ....... };
class multi_thread_model { ....... };

class reference_count { ....... };
class deep_copy       { ....... };
class copy_on_write   { ....... };

// SmartPointer<OwnerShipManagement, ThreadModel>
template <class Ownership, class ThreadModel>
class smart_ptr { ........ };

// Single thread, and reference count method.
smart_ptr<reference_count, single_thread_model> ptr;

// Multi thread, and deep copy method.
smart_ptr<deep_copy, multi_thread_model> ptr;

// Multi thread and copy on write method.
smart_ptr<copy_on_write, multi_thread_model> ptr;


// merit : Combinate option flexibly.
//         => easier adding option than using inheritance.

*/


