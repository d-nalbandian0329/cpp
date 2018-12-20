// Implement Queue by ring buffer structure.
// This queue contains only primitive type data.
#include <iostream>

// Default queue size.
#define SIZE 64

using namespace std;

template <class T>
class Queue{
  class OverFlow{};
  class UnderFlow{};

  virtual void enqueue(T) = 0;
  virtual T    dequeue() = 0;
};

template <class T>
class QueueImple : public Queue<T>{
  T *que;
  int front;
  int rear;
  int max_size;
  int size;

  class OverFlow{};
  class UnderFlow{};

public:
  QueueImple();
  QueueImple(int);
  ~QueueImple();

  void enqueue(T);
  T    dequeue();

  int getMaxSize(){ return this->max_size; }
  int getSize()   { return this->size; }

  void show();
};


template <class T>
QueueImple<T>::QueueImple(){
  front = rear = size = 0;
  max_size = SIZE;

  que = new T[max_size];
}

template <class T>
QueueImple<T>::QueueImple(int max_size){
  front = rear = size = 0;
  this->max_size = max_size;

  que = new T[max_size];
}

template <class T>
QueueImple<T>::~QueueImple(){
  delete [] que;
}

template <class T>
void QueueImple<T>::enqueue(T var){
  if(size >= max_size)
    throw OverFlow();

  ++size;
  que[rear++] = var;

  if(rear >= max_size) rear = 0;
}

template <class T>
T QueueImple<T>::dequeue(){
  T ret;

  if(size <= 0)
    throw UnderFlow();

  --size;
  ret = que[front++];

  if(front >= max_size) front = 0;

  return ret;
}

template <class T>
void QueueImple<T>::show(){
  int i, n;

  i = front;
  n = 0;

  cout << "que :";
  while(n < this->size){
    cout << " " << que[i];
    ++i,++n;
    if(i >= max_size) i = 0;
  }
  cout << endl;

}


int main(){
  QueueImple<int> q1(10);
  int n, i;

  for(i = 0; i < q1.getMaxSize(); i++){
    q1.enqueue(i);
    cout << "EN:" << i << endl;
  }

  q1.show();

  for(i = 0; i < q1.getMaxSize()/2; i++)
    cout << "DE:" << q1.dequeue() << endl;

  q1.show();

  for(i = 0; i < q1.getMaxSize()/2; i++){
    q1.enqueue(i*10);
    cout << "EN:" << i << endl;
  }

  q1.show();

  return 0;
}
