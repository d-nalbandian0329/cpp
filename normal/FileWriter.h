// FileWriter

#include <fstream>
#include <string>


class FileWriter {
public:
	// Scoped enum.  since C++11
	// The underlying type for SaveMode is std::size_t.
	enum class SaveMode : std::size_t { APPEND, TRUNCATE };

	FileWriter(const std::string& file_path = "") : file_path_(file_path) {
	}


	inline void setFilePath(const std::string& file_path) {
		this->file_path_ = file_path;
	}


	template <
		template <class T, class Allocator = std::allocator<T>>
		class Container
	>
	void writeData(const Container<std::string>& container,
					SaveMode mode = SaveMode::APPEND) {
		writeData<Container>(container, this->file_path_, mode);
	}

	template <
		template <class T, class Allocator = std::allocator<T>>
		class Container
	>
	void writeData(const Container<std::string>& container, const std::string& file_path,
					SaveMode mode = SaveMode::APPEND) {
		std::ofstream ofs;

		ofs.exceptions(std::ofstream::failbit | std::ofstream::badbit);

		try {
			switch(mode) {
			case SaveMode::APPEND:
				ofs.open(file_path, std::ios::out | std::ios::app);
				break;

			case SaveMode::TRUNCATE:
				ofs.open(file_path, std::ios::out | std::ios::app);
				break;
			}

			for(std::size_t i = 0; i < container.size(); ++i)
				ofs << container[i] << std::endl;
		}
		catch(const std::ofstream::failure& ex) {
			std::cerr << "Current File : " << file_path << std::endl;
			std::cerr << ex.what() << std::endl;
		}
	}

private:
	std::string file_path_;
};

