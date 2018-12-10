// Strategy Pattern version.

#include <iostream>
#include <string>

class Log {
public:
	virtual ~Log() {};
	virtual void print(const std::string&) const = 0;
};


class DebugLog : public Log {
public:
	void print(const std::string& value) const {
		std::cout << value << std::endl;
	}
};

class ReleaseLog : public Log {
public:
	void print(const std::string&) const {
	}
};


auto main() -> int {
	Log* debug_log = new DebugLog();
	Log* release_log = new ReleaseLog();

	debug_log->print("Fatal Error!!");
	release_log->print("Fatal Error!!");

	return 0;
}

