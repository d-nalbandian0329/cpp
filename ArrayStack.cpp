// This program is for practice to implement Stack interface.
#include <iostream>

// Default size of stack.
#define SIZE 64

using namespace std;


template <class T>
class Stack{
  // Self made exception class.
  class UnderFlow{};
  class OverFlow{};

  virtual void push(T) = 0;
  virtual T pop() = 0;
};


template <class T>
class ArrayStack : public Stack<T>{
  T *p;          // Pointer to Stack body.
  int max_size;  // Max size of this stack.
  int top;       // Next index to top element.

  class UnderFlow{};
  class OverFlow{};

public:
  ArrayStack<T>();
  ArrayStack<T>(int);
  ~ArrayStack<T>();

  void push(T);
  T pop();

  int getMaxSize(){ return this->max_size; }
  int getSize()   { return this->top;      }
};


// Default constructor.
template <class T>
ArrayStack<T>::ArrayStack(){
  this->top = 0;
  this->max_size = SIZE;
  this->p = new T[SIZE];
}

// @para1 : Size of this stack.
template <class T>
ArrayStack<T>::ArrayStack(int max_size){
  this->top = 0;
  this->max_size = max_size;
  this->p = new T[max_size];
}

template <class T>
ArrayStack<T>::~ArrayStack(){
  delete [] this->p;
}

template <class T>
void ArrayStack<T>::push(T var){
  if(top >= max_size)
    throw OverFlow();

  p[top++] = var;
}

template <class T>
T ArrayStack<T>::pop(){
  if(top <= 0)
    throw UnderFlow();

  return p[--top];
}



int main(){
  ArrayStack<long> ias1, ias2(10);
  int num;

  cout << "MAX  : " << ias1.getMaxSize() << endl;
  cout << "SIZE : " << ias1.getSize() << endl;

  for(int i = 0; (i<ias1.getMaxSize()) && (i<10); i++)
    ias1.push(i);

  num = ias1.getSize();
  cout << "Pop element from stack.\n";
  for(int i = 0; i < num; i++)
    cout << ias1.pop() << endl;


  cout << "MAX  : " << ias2.getMaxSize() << endl;
  cout << "SIZE : " << ias2.getSize() << endl;

  for(int i = 0; (i<ias2.getMaxSize()) && (i<10); i++)
    ias2.push(i);

  num = ias2.getSize();
  cout << "Pop element from stack.\n";
  for(int i = 0; i < num; i++)
    cout << ias2.pop() << endl;

  return 0;
}
