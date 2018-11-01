#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
  T *pMem;
  int size;
  int top;
public:
  TStack(int _size = MaxStackSize) {
	  if (_size < 1 || _size > MaxStackSize) throw "ERROR";
	  size = _size;
	  top = -1;
	  pMem = new T[size];
  }
  ~TStack()
  {
    delete [] pMem;
  }
  bool empty() {
	  return top == -1;
  }
  bool full() {
	  return top == size - 1;
  }
  void clear() {
	  top = -1;
  }
  void pop() {
	  if (!empty()) top--;
  }
  T front() {
	  return pMem[top];
  }
  void push(T n) {
	  pMem[++top] = n;
  }
  int lenght() {
	  return top + 1;
  }
};

#endif
