#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_same.hpp>

#include <chrono>
#include <vector>
#include <functional>

namespace my_std {
	template <bool use_swap> struct iter_swap_impl;

	template <class ForwardIterator1, class ForwardIterator2>
	void iter_swap(ForwardIterator1 ite1, ForwardIterator2 ite2) {
		// 値の型が一致してreferenceが真の参照である場合
		// std::swapを使用する
		// std::vector<bool>がProxy参照であるため必要な対応
		typedef std::iterator_traits<ForwardIterator1> traits1;
		typedef typename traits1::value_type v1;
		typedef typename traits1::reference r1;

		typedef std::iterator_traits<ForwardIterator2> traits2;
		typedef typename traits2::value_type v2;
		typedef typename traits2::reference r2;


		const bool use_swap = boost::is_same<v1, v2>::value
								&& boost::is_reference<r1>::value
								&& boost::is_reference<r2>::value;

		iter_swap_impl<use_swap>::do_it(ite1, ite2);
	}

	template <>
	struct iter_swap_impl<true> {
		template <class ForwardIterator1, class ForwardIterator2>
		static void do_it(ForwardIterator1 ite1, ForwardIterator2 ite2) {
			std::swap(*ite1, *ite2);
		}
	};

	template <>
	struct iter_swap_impl<false> {
		template <class ForwardIterator1, class ForwardIterator2>
		static void do_it(ForwardIterator1 ite1, ForwardIterator2 ite2) {
			typename std::iterator_traits<ForwardIterator1>::value_type
				temp = *ite1;
			*ite1 = *ite2;
			*ite2 = temp;
		}
	};

}


template <class Predicate, class TimeType>
auto measureTime(Predicate predicate, TimeType time_type) -> TimeType {
	auto start = std::chrono::system_clock::now();

	predicate();

	auto end = std::chrono::system_clock::now();

	return std::chrono::duration_cast<TimeType>(end - start);
}


void doAllProcess() {

	{
		std::vector<int> v_int1 {1};
		std::vector<int> v_int2 {100};

		auto func = std::bind(
						my_std::iter_swap<std::vector<int>::iterator,std::vector<int>::iterator>,
						std::begin(v_int1), std::begin(v_int2));

		auto period = measureTime(func, std::chrono::nanoseconds());

		std::cout << "std::vector<int>\n=> " << period.count() << " [micro sec]" << std::endl;
	}


	{
		std::vector<bool> v_bool1 {true};
		std::vector<bool> v_bool2 {false};

		auto func = std::bind(
						my_std::iter_swap<std::vector<bool>::iterator,std::vector<bool>::iterator>,
						std::begin(v_bool1), std::begin(v_bool2));

		auto period = measureTime(func, std::chrono::nanoseconds());

		std::cout << "std::vector<bool>\n=> " << period.count() << " [micro sec]" << std::endl;
	}

}

auto main() -> int {
	doAllProcess();

	return 0;
}

