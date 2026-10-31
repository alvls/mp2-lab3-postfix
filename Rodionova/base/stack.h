#ifndef __STACK_H__
#define __STACK_H__
#include <stdexcept>

const int MaxStackSize = 100;

template <class T>
class TStack
{
  T *pMem;
  int size;
  int top;
public:
  TStack(int _size)
  {
    size = _size;
    top = -1;
    if ((size < 1) || (size > MaxStackSize))
      throw size;
    pMem = new T[size];
  }
  ~TStack()
  {
    delete [] pMem;
  }
  void Push(const T& val)
  {
      if (top >= size - 1)
          throw std::out_of_range("Stack overflow");
      top++;
      pMem[top] = val;
  }
  T Pop()
  {
      if (top < 0)
          throw std::out_of_range("Stack is empty");
      T val = pMem[top];
      top--;
      return val;
  }
  T Top() const
  {
      if (top < 0)
          throw std::out_of_range("Stack is empty");
      return pMem[top];
  }
  bool IsEmpty() const
  {
      return top == -1;
  }
};

#endif
