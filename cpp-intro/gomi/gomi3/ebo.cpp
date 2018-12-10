#include <iostream>
#include <cstdlib>


// EBO(Empty Base Optimization)
// => 型を継承した時に追加のサイズを持たせない最適化


namespace test{
	// データメンバを持たず継承もしてない,　データとしての要素のない
	// クラスだとしても必ずサイズを持つ
	// => インスタンス化された際にオブジェクトのアドレスを取れるようにするため
	class EmptyClass {};

	// Hoge のサイズはデータメンバのiの分とEmptyClassの分
	// sizeof(Hoge) > sizeof(int)
	class Hoge {
		int i;
		EmptyClass e;
	};

	void test() {
		std::cout << "EmptyClass : " << sizeof(EmptyClass) << std::endl;
		std::cout << "Hoge       : " << sizeof(Hoge) << std::endl;
		std::cout << "int        : " << sizeof(int) << std::endl;
	}
}

namespace test2 {
	// 規格では空の型が別の型を継承していて継承元の型が既にサイズを
	// 持っている場合や, 逆に空の型の継承先がサイズを持っている場合
	// EmptyClass 自体の追加のサイズは無くしてもよいことになっている
	class Int { int i; };
	class EmptyClass : Int {};

	void test() {
		std::cout << "Int        : " << sizeof(Int) << std::endl;
		std::cout << "EmptyClass : " << sizeof(EmptyClass) << std::endl;
	}
}


namespace test3 {
	class MyAllocator {
	public:
		void* allocate(std::size_t size) {
			return std::malloc(size);
		}
		// 以下略
	};

	// EBOを意識しない設計のContainer
	template <class T, class Allocator>
	class ContainerNotEBO {
		// data member
		T* data_ = nullptr;
		std::size_t capacity_;
		Allocator allocator_;

	public:
		ContainerNotEBO(std::size_t capacity)
			: capacity_(capacity_),
				data_(nullptr),
				allocator_()
		{
			data_ = reinterpret_cast<T*>(allocator_.allocate(sizeof(T) * capacity_));
		};

		// 以下略
	};


	// EBOを意識した設計のContainerクラス
	template <class T, class Allocator>
	class ContainerEBO : public Allocator {
		// data member.
		T* data_ = nullptr;
		std::size_t capacity_;

	public:
		ContainerEBO(std::size_t capacity)
			: capacity_(capacity),
				data_(nullptr)
		{
			data_ = reinterpret_cast<T*>(this->allocate(sizeof(T) * capacity_));
		}

		// 以下略
	};

	void test() {
		using NotEBO = ContainerNotEBO<int,MyAllocator>;
		using EBO = ContainerEBO<int,MyAllocator>;

		std::cout << "MyAllocator     : " << sizeof(MyAllocator) << std::endl;
		std::cout << "ContainerNotEBO : " << sizeof(NotEBO) << std::endl;
		std::cout << "ContainerEBO    : " << sizeof(EBO) << std::endl;
	}
}


int main() {
	test3::test();
}

