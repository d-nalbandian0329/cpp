// Policy.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <memory>
#include <string>
#include <exception>
#include <type_traits>


#include <array>


struct has_readDataFromFile_impl {
	template <class T>
	static auto check(T*) -> decltype(T::readDataFromFile(""), std::true_type());

	template <class T>
	static auto check(...) -> std::false_type;
};

template <class T>
class has_readDataFromFile : public decltype(has_readDataFromFile_impl::check<T>(nullptr)) {
};


template <class FileReaderPolicy = AsciiFileReaderPolicy,
			typename std::enable_if<has_readDataFromFile<FileReaderPolicy>::value>::type* = nullptr>
class FileReader {
public:
	FileReader(const std::string& file_path = std::string("./data.dat"))
		: file_path_(file_path) {}

	FileReader(std::string&& file_path) : file_path_(std::move(file_path)) {}

	~FileReader() = default;

	auto readDataFromFile() {
		return std::move(readDataFromFile(this->file_path_));
	}

	auto readDataFromFile(const std::string& file_path) {
		return std::move(FileReaderPolicy::readDataFromFile(file_path));
	}

private:
	std::string file_path_;
};


// Used for reading ascii file.
class AsciiFileReaderPolicy {
public:
	static auto readDataFromFile(const std::string& file_path) -> std::vector<std::string> {
		std::ifstream ifs;

		ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		std::vector<std::string> ret {};
		int line = 0;

		try {
			ifs.open(file_path, std::ios::in);

			std::string buff;

			while (std::getline(ifs, buff))
				++line, ret.push_back(buff);
		}
		catch (std::ifstream::failure& ex) {
			if (!ifs.eof()) {
				std::cerr << "Error occurs at line " << line << "." << std::endl;
				std::cerr << ex.what() << std::endl;
			}
		}
		catch (std::exception& ex) {
			std::cerr << "Error occurs at line " << line << "." << std::endl;
			std::cerr << ex.what() << std::endl;
		}

		return ret;
	}
};



// Used for reading ascii file.
class BinaryFileReaderPolicy {
public:
	static auto readDataFromFile(const std::string& file_path) -> std::pair<std::unique_ptr<char[]>, std::size_t> {
		std::ifstream ifs;

		ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			ifs.open(file_path, std::ios::in | std::ios::binary);

			// ファイルサイズの確認
			ifs.seekg(0, std::ios::end);
			std::size_t file_size = ifs.tellg();
			ifs.seekg(0, std::ios::beg);

			std::unique_ptr<char[]> byte_data(new char[file_size]);

			ifs.read(byte_data.get(), file_size);

			return std::make_pair(std::move(byte_data), file_size);
		}
		catch (std::ifstream::failure& ex) {
			if (!ifs.eof()) {
				std::cerr << ex.what() << std::endl;
			}
		}
		catch (std::exception& ex) {
			std::cerr << ex.what() << std::endl;
		}
	}
};



struct is_indexable_impl {
	template <class T>
	static auto check(T*) -> decltype(std::declval<T>().operator[](0), std::true_type());

	template <class T>
	static auto check(...) -> std::false_type;
};

template <class T>
class is_indexable : public decltype(is_indexable_impl::check<T>(nullptr)) {};



struct has_size_impl {
	template <class T>
	static auto check(T*) -> decltype(std::declval<T>().size(), std::true_type());

	template <class T>
	static auto check(...)->std::false_type;
};

template <class T>
class has_size : public decltype(has_size_impl::check<T>(nullptr)) {};



template <class FileWriterPolicy>
class FileWriter {
public:
	FileWriter(const std::string& file_path = std::string("./data.dat"))
		: file_path_(file_path) {}

	FileWriter(std::string&& file_path) : file_path_(std::move(file_path)) {}

	~FileWriter() = default;

	template <class IndexableContainer>
	bool writeDataToFile(IndexableContainer&& container) {
		return writeDataToFile(this->file_path_, std::forward<IndexableContainer>(container));
	}

	template <class IndexableContainer,
				typename std::enable_if<
					is_indexable<IndexableContainer>::value
					&&
					has_size<IndexableContainer>::value>::type* = nullptr>
	bool writeDataToFile(const std::string& file_path, IndexableContainer&& container) {
		return FileWriterPolicy::writeDataToFile(file_path, std::forward<IndexableContainer>(container));
	}


	// size() 持ってない方
	template <class IndexableContainer>
	bool writeDataToFile(IndexableContainer&& container, std::size_t total_size) {
		return writeDataToFile(this->file_path_, std::forward<IndexableContainer>(container), total_size);
	}

	template <class IndexableContainer, typename std::enable_if<is_indexable<IndexableContainer>::value>::type* = nullptr>
	bool writeDataToFile(const std::string& file_path, IndexableContainer&& container, std::size_t total_size) {
		return FileWriterPolicy::writeDataToFile(file_path, std::forward<IndexableContainer>(container), total_size);
	}
private:
	std::string file_path_;
};

class AsciiWriterPolicy {
public:
	template <class IndexableContainer>
	static auto writeDataToFile(const std::string& file_path, IndexableContainer&& container) -> bool {
		std::ofstream ofs;

		ofs.exceptions(std::ofstream::failbit | std::ofstream::badbit);

		try {



			return true;
		}
		catch (std::exception& ex) {


		}
	}
};


void test() {
	FileReader<> ascii{"D:/KRC/text.txt"};

	auto&& data_set = ascii.readDataFromFile();

	for (auto&& data : data_set)
		std::cout << data << std::endl;
}

class X {};
void test2() {
	std::cout << std::boolalpha;
	std::cout << has_readDataFromFile<AsciiFileReaderPolicy>::value << std::endl;
	std::cout << has_readDataFromFile<BinaryFileReaderPolicy>::value << std::endl;
	std::cout << has_readDataFromFile<X>::value << std::endl;

	//FileReader<X> bug_class{""};
}


// 組み込み型の配列型がうまくいかん
void test3() {
	std::cout << std::boolalpha;
	std::cout << is_indexable<std::vector<int>>::value << std::endl;
	std::cout << is_indexable<std::array<int,1>>::value << std::endl;
	std::cout << is_indexable<int(&)[]>::value << std::endl;
	std::cout << is_indexable<std::unique_ptr<char[]>>::value << std::endl;
	std::cout << is_indexable<X>::value << std::endl;
}


int main() {

	//test();

	test3();

	getchar();
	return 0;
}

