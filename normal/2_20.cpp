#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

class PhoneBook {
private:
	struct Record {
		string name;
		string phone;
		Record(const string& n, const string& p) : name(n), phone(p){}
		
		friend ostream& operator<<(ostream& stream, const Record& record){
			return stream << record.name << " : " << record.phone;
		}
	};

	vector<Record> book;

public:
	void add(const string& name, const string& phone){
		book.emplace_back(name, phone);
	}

	void print(ostream& stream) const {
		copy(begin(book), end(book), ostream_iterator<Record>(stream, "\n"));
	}

};


/*
namespace std {
	template<class InputIterator, class OutputIterator>
	OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result);
}

概要 : 指定された範囲のコピーを行う

要件 : resultは[first,last)の範囲に含まれてはならない


namespace std {
	template <class T, class CharT = char, class Traits = char_traits<CharT>>
	class ostream_iterator
		: public iterator<output_iterator_tag, void, void, void, void>
}

概要：output_iteratorは出力イテレータ
　　　代入の際に外部から渡されたostreamオブジェクトにoperator<<()
　　　で値を出力するイテレータアダプタ

ex.)
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

int main(){
	const std::vector<int> v = {1, 2, 3};

	// vの要素をイテレートしながらstd::coutに出力, 区切り文字はカンマ
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ","));
}

*/


int main(){
	PhoneBook pb;

	pb.add("police", "110");

	pb.add("fire", "119");

	pb.add("weather", "177");
	
	pb.print(std::cout);

	return 0;
}

