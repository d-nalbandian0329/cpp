#ifndef HOKUYO_DUMMY_H
#define HOKUYO_DUMMY_H


#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <utility>


class HokuyoDummy {
	using HokuyoData = std::pair<uint64_t, std::vector<uint16_t>>;
	using HokuyoDataSet = std::vector<HokuyoData>;

public:
	HokuyoDummy(std::size_t data_num = 1081, std::size_t min_dist = 10, std::size_t max_dist = 60000)
		: data_num_(data_num), mt_(std::mt19937_64(seed_gen_())),
			dist_(std::move(std::uniform_int_distribution<>(min_dist,max_dist))) {
	}

	auto get_distance() -> HokuyoData {
		uint64_t time_stamp
			= std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::high_resolution_clock::now().time_since_epoch()).count();

		std::vector<uint16_t> distances(data_num_);
		for(std::size_t i = 0; i < data_num_; ++i)
			distances[i] = dist_(mt_);

		return std::move(std::make_pair(time_stamp, distances));
	}


	void test() {
		std::uniform_int_distribution<> dist(0, 99);

		std::cout << "data :";
		for(int i = 0; i < 10; ++i)
			std::cout << " " << dist(mt_);
		std::cout << std::endl;
	}


private:
	std::random_device seed_gen_;
	std::mt19937_64 mt_;
	std::uniform_int_distribution<> dist_;
	std::size_t data_num_;
	std::size_t min_dist_;
	std::size_t max_dist_;
};

#endif

