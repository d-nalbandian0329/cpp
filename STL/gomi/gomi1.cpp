#include <iostream>
#include <unordered_map>
#include <vector>

/*
namespace std {
	template <class Key,
				class T,
				class Hash = std::hash<Key>,
				class Pred = std::equal_to<Key>,
				class Allocator = std::allocator<std::pair<const Key, T>>
	>
	class unordered_map;
}

@abstract:
同一キーの格納不可, 格納順が規定されていない

同じキーに複数回値を設定すると最後に設定した値になる

追加処理に要するコスト O(1)

値が設定されていないキーを指定して値を取得すると値型のデフォルトが返される
*/

namespace t1 {
	// そのままキーとして用いることができない型をキーに指定するには
	// ハッシュ関数オブジェクトを用意する

	class HashVI {
	public:
		std::size_t operator()(const std::vector<char>& x) const {
			const int C = 997;

			std::size_t ret = 0;
			for(int i = 0; i != x.size(); ++i)
				ret = ret * C + x[i];

			return ret;
		}

	};

	void test() {
		// build error
		//std::unordered_map<std::vector<int>, int> map;
		// ok
		//std::unordered_map<std::vector<int>,int,HashVI> map;

		std::unordered_map<std::string,char> mp1;
		std::unordered_map<int,double> mp2;
		std::unordered_map<std::string,std::string> mp3;
		std::unordered_map<std::vector<char>,int,HashVI> mp4;

	}
}



auto main() -> int {
	t1::test();
}

