#include <utility>

class FileManager {
	FileManager(const std::string& file_path = "") : file_path_(file_path) {
	}

	inline void setFilePath(const std::string& file_path) {
		this->file_path_ = file_path;
	};

	


private:
	std::unique_ptr<FileReader> reader_;
	std::unique_ptr<FileWriter> writer_;

	std::string file_path_;
};

