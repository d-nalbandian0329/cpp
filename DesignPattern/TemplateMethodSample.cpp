// Template Method Pattern
// ある大まかな処理は一緒だが, それぞれの場合において細かい
// 部分だけ変化させるようなソフトウェアを作成したい時に利用.
// 大まかな処理をあるクラス(スーパークラス)に記述しそのクラスを
// 継承するクラス(サブクラス)にそれぞれ変化する部分の処理を記述する.

// Template Method Pattern で暮らす設計をする上で
// リスコフの置換原則を守ることが大事
// LSP(Liskov Substitution Principle)  Barbara Liskov
// 基本型で決められた約束を派生型で破ってはならない
// 同じスーパークラスを継承したサブクラスであるにもかかわらず
// 同じ名前の関数で返り値や処理が異なってはいけない.


#include <iostream>
#include <string>
#include <memory>


// 文字列表示用のテンプレートクラス
class AbstractDisplay {
public:
	virtual ~AbstractDisplay() = default;

	// 文字列表示の始まり
	virtual void open() {}

	// 文字列の表示
	virtual void print() {}

	// 文字列表示の終わり
	virtual void close() {}

	// データを表示する関数
	void display() {
		open();

		for(int i = 0; i < 5; ++i)
			print();

		close();
	}
};



// シンプルな文字列表示クラス
class SimpleDisplay : public AbstractDisplay {
public:
	SimpleDisplay(std::string str) : str_(str) {
		len_ = str.length();
	}

	void open() override {
		std::cout << "+";

		for(int i = 0; i < len_; ++i)
			std::cout << "-";

		std::cout << "+" << std::endl;
	}

	void print() override {
		std::cout << "|" << str_ << "|" << std::endl;
	}

	void close() override {
		open();
	}

private:
	std::string str_;
	int len_;
};



// ちょっと豪華な文字列表示クラス
class GorgeousDisplay : public AbstractDisplay {
public:
	GorgeousDisplay(std::string str) : str_(str) {
		len_ = str.length();
	}

	void open() override {
		std::cout << "*";
		for(int i = 0; i < len_; ++i)
			std::cout << "=";
		std::cout << "*" << std::endl;
	}

	void print() override {
		std::cout << "#" << str_ << "#" << std::endl;
	}

	void close() override {
		open();
	}

private:
	std::string str_;
	int len_;
};


auto main() -> int {

	std::unique_ptr<AbstractDisplay> simple(new SimpleDisplay("SimpleDisplay"));
	std::unique_ptr<AbstractDisplay> gorgeous(new GorgeousDisplay("GorgeousDisplay"));

	simple->display();
	gorgeous->display();
}

