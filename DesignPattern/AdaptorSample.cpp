// Advapter pattern
// 2つのインターフェースが異なるクラスをつなげるための
// クラスを作成するデザインパターン.
// 実績のあるクラスをバージョンアップする際に既存の
// クラスを変更せずにAdapterクラスを作成することで
// 新しいAPIに対応させることができる.

// Adapter Pattern は以下の2種類
// 1 : 既存のクラスを継承して新しいAdapterクラスを作成
// 2 : 新しいクラスが既存のクラスのインスタンスを持つ

#include <iostream>
#include <string>

// 日本語で表示指令を行うインターフェースクラス
class PrintInterface {
public:
	virtual ~PrintInterface() = default;
	virtual std::string Kakko(std::string) = 0;
	virtual std::string DaburuKakko(std::string) = 0;
};


class EnglishPrint {
public:
	std::string Brackets(std::string str) {
		return ("[" + str + "]");
	}

	std::string DoubleBrackets(std::string str) {
		return ("[[" + str + "]]");
	}
};


// 英語Printクラスを使用した日本語adaptor
class JapanesePrint : public PrintInterface {
public:
	std::string Kakko(std::string str) override {
		return eng_.Brackets(str);
	}

	std::string DaburuKakko(std::string str) override {
		return eng_.DoubleBrackets(str);
	}

private:
	EnglishPrint eng_;
};


auto main() -> int {
	EnglishPrint eng;
	std::cout << eng.Brackets("Hi") << std::endl;
	std::cout << eng.DoubleBrackets("Ho") << std::endl;

	JapanesePrint jap;
	std::cout << jap.Kakko("こんにちは") << std::endl;
	std::cout << jap.DaburuKakko("ほー") << std::endl;

	return 0;
}

