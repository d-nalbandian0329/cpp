#include <iostream>
#include <cstdlib>
#include <exception>
#include <new>

// new operator
// 1. allocate storage
// 2. construct object

// delete operator
// 1. destruct object
// 2. release storage

// メモリの確保や解放の部分はnew, delete演算子をオーバーロードする
// ことでその内容を変更できる

// default
// void* operator new(std::size_t) throw(std::bad_alloc);
// void* operator new[](std::size_t) throw(std::bad_alloc);
// void operator delete(void*) throw();
// void operator delete[](void*) throw();


// 配置構文
// Type* p = new(std::nothrow) Type();
// std::nothrow : std::nothrow_t型, <new>で定義
// std::nothrowを指定することでメモリ確保に失敗した時に例外(std::bad_alloc)
// を送出するのではなくnull pointerを返すようになる
// ただし, オブジェクト生成の段階で例外が送出された場合はnew演算子のある部分
// にまで例外がやってくるので非推奨

// 確保済みの領域を使用する場合, 置換不可
// void* operator new(std::size_t, void*) noexcept;

// placement new
namespace n1 {
	class X {};

	void test() {
		void* p = std::malloc(sizeof(X));
		X* xp = new(p) X();

		std::cout << std::hex;
		std::cout << "p  : " << p << std::endl;
		std::cout << "xp : " << xp << std::endl;

		// 明示的にdestructorを呼び出す必要がある
		xp->~X();
		std::free(p);
	}
}

namespace n2 {
	class MyClassException : public std::exception {
	public:
		const char* what() const noexcept override {
			return "MyClassException";
		}
	};


	class MyClass {
	public:
		MyClass() { throw MyClassException(); }
		void func() { std::cout << "MyClass" << std::endl; }
	};

	class MyClassHandler {
	public:
		// function try block
		MyClassHandler() try : p_(new MyClass()) {
		}
		catch(std::exception& ex) {
			std::cout << ex.what() << std::endl;
			std::abort();
		}


		// メンバ初期化時に発生した例外と基底クラスで発生した例外は
		// function-try-block でないと捕捉できない
		/*
		MyClassHandler() : p_(new MyClass()) {
			try {
			}
			catch(std::exception& ex) {
				std::cout << ex.what() << std::endl;
				std::abort();
			}
		}
		*/

		~MyClassHandler() {
			delete p_;
		}

		void doit() {
			p_->func();
		}

	private:
		MyClass* p_;
	};


	void test() {
		MyClassHandler obj;
		obj.doit();
	}
}



int main() {
	n2::test();
}



