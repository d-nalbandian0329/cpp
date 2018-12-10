#include <iostream>

using namespace std;

template <class T>
struct _is_void {
	static const bool value = false;
};

// full specialization / explicit specialization
template <>
struct _is_void < void > {
	static const bool value = true;
};


// trailing return type syntax
auto main() -> int {
	cout << boolalpha;
	cout << _is_void<void>::value << endl;
	cout << _is_void<int>::value << endl;
	cout << _is_void<char*>::value << endl;

	return 0;
}

