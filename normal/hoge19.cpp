#include <iostream>
#include <chrono>
#include <ctime>


class TimeConverter {
public:
	TimeConverter(int year=1900, int month=1, int mday=1,
					int hour=0, int minute=0, int sec=0, int msec=0) {

		struct tm buff {
			sec,
			minute,
			hour,
			mday,
			month - 1,
			year - 1900
		};

		tp_ = std::chrono::system_clock::from_time_t(std::mktime(&buff));
		
		tp_ += std::chrono::milliseconds(msec);
	}


	TimeConverter(std::chrono::system_clock::time_point&& tp) {
		tp_ = std::move(tp);
	}


	std::uint64_t getEpoch() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(tp_.time_since_epoch()).count();
	}

private:
	std::chrono::system_clock::time_point tp_;

};



int main() {
	TimeConverter t(std::chrono::system_clock::now());

	std::cout << t.getEpoch() << std::endl;

	getchar();

	return 0;
}

