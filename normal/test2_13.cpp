#include <iostream>
#include <string>
#include "RWProperty.h"

using namespace std;

class Cat {
private:
	int age_;
	string name_;

	int set_age(const int& age) {
		return age_ = age;
	}
	int get_age() const {
		return age_;
	}
	string set_name(const string& name) {
		return name_ = name;
	}
	string get_name() const {
		return name_;
	}

public:
	RWProperty<int, Cat, &Cat::get_age, &Cat::set_age> age;
	RWProperty<string, Cat, &Cat::get_name, &Cat::set_name> name;

	// 自分自身をこれらのプロパティの所有者に指定
	Cat(){ age(this); name(this); }
};

int main() {
	Cat aCat;
	aCat.age = 4;
	aCat.name = "tama";

	int age = aCat.age;
	string name = aCat.name;

	std::cout << name << " : " << age << std::endl;
}

