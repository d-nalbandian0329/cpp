#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Plain {
public:
	virtual string convert(const string& str) const {
		return str;
	}
};

// パラメータ化継承
template <class Base = Plain>
class Bold : public Base {
public:
	// コンストラクタの継承
	using Base::Base;

	virtual string convert(const string& str) const {
		return ("<b>" + Base::convert(str) + "</br>");
	}
};

template <class Base = Plain>
class Italic : public Base {
public:
	using Base::Base;

	virtual string convert(const string& str) const {
		return ("<i>" + Base::convert(str) + "</i>");
	}
};


template <class Base = Plain>
class Size : public Base {
	string size_;

public:
	using Base::Base;

	Size(int s) {
		ostringstream strm;
		strm << s;
		size_ = strm.str();
	}

	virtual string convert(const string& str) const {
		return ("<font size='" + size_ + "'>" + Base::convert(str) + "</font>");
	}

};

int main() {
	Plain p;
	Bold<> b;
	Italic<> i;
	// 多重パラメータ化継承
	Size<Bold<Italic<>>> sbi(5);
	Italic<Size<>> si(3);

	Plain* converter[5] = { &p, &b, &i, &sbi, &si };

	for(Plain* c : converter) {
		cout << c->convert("Hello, C++") << endl;
	}

	return 0;
}

