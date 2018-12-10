#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>

struct SharedResource {
	SharedResource() : flag_(false) {}
	std::mutex mutex_;
	std::condition_variable cv_;
	bool flag_;
};

SharedResource resource;



void f() {
	std::unique_lock<std::mutex> locker(resource.mutex_);
	resource.cv_.wait(locker, [&](){ return resource.flag_; });
	std::cout << "f" << std::endl;
}


void g() {
	std::unique_lock<std::mutex> locker(resource.mutex_);
	resource.cv_.wait(locker, [&](){ return !resource.flag_; });
	std::cout << "g" << std::endl;
	resource.flag_ = true;
	resource.cv_.notify_one();
}



auto main() -> int {
	std::thread th_f(f);
	std::thread th_g(g);

	th_f.join();
	th_g.join();
}

