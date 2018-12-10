// FileReader

#include <fstream>
#include <string>
#include <utility>

/*
struct has_push_back_func_impl {
	template <
		template <class T, class Allocator = std::allocator<T>>
		class Container
	>
	static auto check(Container*) -> decltype(
		std::declval<Container>().push_back(std::declval<T>()),
		std::true_type()
	);

	template <
		template <class T, class Allocator = std::allocator<T>>
		class Container
	>	
	static auto check(...) -> std::false_type;
};


template <
	template <class T, class Allocator = std::allocator<T>>
	class Container
>
struct has_push_back_func
	: decltype(has_push_back_func_impl::check<Container>(nullptr)) {
};
*/

class FileReader {
public:
	FileReader(const std::string& file_path = "") : file_path_(file_path) {
	}


	inline void setFilePath(const std::string& file_path) {
		this->file_path_ = file_path;
	}


	// Container class must have push_back function.
	template <
		template <class T, class Allocator = std::allocator<T>>
		class Container
	>
	Container<std::string> readData() {
//		static_assert(has_push_back_func<Container>::value,
//						"This class has no push_back function.\n");

		return readData<Container>(this->file_path_);
	}

	// Container class must have push_back function.
	template <
		template <class T, class Allocator = std::allocator<T>>
		class Container
	>
	Container<std::string> readData(const std::string& file_path) {
//		static_assert(has_push_back_func<Container>::value,
//						"This class has no push_back function.\n");

		Container<std::string> container;

		std::ifstream ifs;

		ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		int line = 0;
		try {
			ifs.open(file_path, std::ios::in);

			std::string buff;
			while(std::getline(ifs, buff))
				++line, container.push_back(buff);
		}
		catch(const std::ifstream::failure& ex) {
			if(!ifs.eof()){
				std::cerr << "Current File Path : " << file_path << std::endl;
				std::cerr << "Error occurs at line " << line << std::endl;
				std::cerr << ex.what() << std::endl;
			}
		}

		return container;
	}

private:
	std::string file_path_;	
};

