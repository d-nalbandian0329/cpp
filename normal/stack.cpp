#include "stack.h"

template <class T>
Stack<T>::Stack(int n) : capacity_(n), index_(0) {
	data_ = new T[capacity_];
}

template <class T>
Stack<T>::~Stack() {
	delete[] data_;
}

template <class T>
void Stack<T>::push(T x) {
	if(index_ < capacity_)
		data_[index_++] = x;
}

template <class T>
T Stack<T>::top() const {
	return data_[index_-1];
}

template <class T>
void Stack<T>::pop() {
	if(index_ > 0)
		--index_;
}

template <class T>
int Stack<T>::size() const {
	return index_;
}

// リンクエラー回避のための明示的インスタンス化
template class Stack<int>;

