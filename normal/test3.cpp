#include <iostream>
#include <chrono>

inline uint64_t getCurrentTime() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();
}


// trailing return type syntax
auto main() -> int {
	std::cout << "Now : " << getCurrentTime() << std::endl;

	return 0;
}

