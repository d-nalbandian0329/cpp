#ifndef _STACK_H_
#define _STACK_H_

template <class T>
class Stack {
private:
	T* data_;
	int capacity_;
	int index_;

public:
	explicit Stack(int n);
	~Stack();

	void push(T x);
	T top() const;
	void pop();
	int size() const;
};

#endif // _STACK_H_
