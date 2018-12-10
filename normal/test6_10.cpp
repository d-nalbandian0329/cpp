#include <iostream>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>


using namespace boost::multi_index;

// Container kept elements in order of insertion.
template <class T>
using SeqContainer = multi_index_container<
	T,
	indexed_by<sequenced<>>
>;


// Container kept elements sorted.
template <class T>
using OrdContainer = multi_index_container<
	T,
	indexed_by<ordered_unique<identity<T>>>
>;


auto main() -> int {
	SeqContainer<int> seq;
	seq.push_back(3);
//	seq.insert(4);	// Compile Error!!
					// Because SeqContainer doesn't have insert().

	OrdContainer<int> ord;
	ord.insert(3);
//	ord.push_back(1);	// Compile Error!!
						// Because OrdContainer doesn't have push_back().

}

