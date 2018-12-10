#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include "FileWriter.h"
#include "FileReader.h"

#include <map>


using namespace std;

void readerTest() {
	const string& file_path("/home/takeshi/Program/LISP/test27.lisp");

	FileReader reader(file_path);
	vector<string> container {};

	//reader.readData<map>();

	container = reader.readData<vector>();

	for(auto&& e : container)
		std::cout << e << std::endl;

	//for(auto ite = std::begin(container); ite != std::end(container); ++ite)
	//	std::cout << *ite << std::endl;

	getchar();
}


void writerTest() {
	const string& save_path("/home/takeshi/writer_test.txt");

	FileWriter writer(save_path);

	vector<string> vec {};
	vec.push_back("hoge");
	vec.push_back("fuga fuga");
	vec.push_back("for file in * ; do if [ -f $file ] ; then echo $file ; fi ; done");

	writer.writeData(vec, FileWriter::SaveMode::TRUNCATE);
}



// trailing return type syntax.
auto main() -> int {

	//readerTest();

	writerTest();

	return 0;
}

