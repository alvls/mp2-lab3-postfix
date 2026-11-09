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
  TStack(int _size = MaxStackSize)
  {
    if ((_size < 1) || (_size > MaxStackSize))
      throw std::out_of_range("TStack: invalid size");
    size = _size;
    top  = -1;
    pMem = new T[_size];
  }

  TStack(const TStack& other)
  {
    size = other.size;
    top  = other.top;
    pMem = new T[size];
    for (int i = 0; i <= top; ++i) pMem[i] = other.pMem[i];
  }

  TStack& operator=(const TStack& other)
  {
    if (this != &other)
    {
      delete[] pMem;
      size = other.size;
      top  = other.top;
      pMem = new T[size];
      for (int i = 0; i <= top; ++i) pMem[i] = other.pMem[i];
    }
    return *this;
  }

  ~TStack() { delete[] pMem; }

  void Push(const T& v)
  {
    if (IsFull())
      throw std::overflow_error("TStack: stack is full");
    pMem[++top] = v;
  }

  T Pop()
  {
    if (IsEmpty())
      throw std::underflow_error("TStack: stack is empty");
    return pMem[top--];
  }

  T Top() const
  {
    if (IsEmpty())
      throw std::underflow_error("TStack: stack is empty");
    return pMem[top];
  }

  bool IsEmpty() const { return top == -1; }
  bool IsFull()  const { return top == size - 1; }
  int  Size()    const { return top + 1; }
  void Clear()         { top = -1; }
};

#endif