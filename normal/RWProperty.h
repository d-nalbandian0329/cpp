/*
N615: C++ Properties -- a Library Solution
*/

#include <iostream>

template <class T, class Object,		// プロパティの型
			T (Object::*real_getter)() const,	// getterの型
			T (Object::*real_setter)(const T&)> // setterの型
class RWProperty {
	Object* my_object;

public:
	// プロパティのオーナーの設定
	void operator()(Object* obj) {
		my_object = obj;
	}

	// 関数呼び出しによるget/set
	// メンバへのポインタを経由してメンバを呼び出しているので
	// ->* 演算子を利用している
	T operator()() const {
		return (my_object->*real_getter)();
	}

	T operator()(const T& value) {
		return (my_object->*real_setter)(value);
	}

	// メンバ関数 get/set
	T get() const {
		return (my_object->*real_getter)();
	}
	T set(const T& value) {
		return (my_object->*real_setter)(value);
	}

	// 代入演算子 '=' によるアクセス
	operator T() const {
		return (my_object->*real_getter)();
	}
	T operator=(const T& value){
		return (my_object->*real_setter)(value);
	}

	typedef T value_type;
};

