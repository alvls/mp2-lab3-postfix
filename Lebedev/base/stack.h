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
    size = _size;
    top = -1;
    if ((size < 1) || (size > MaxStackSize))
      throw std::invalid_argument("Wrong stack size");
    pMem = new T[size];
  }
  TStack(const TStack &s)
  {
    size = s.size;
    top = s.top;
    pMem = new T[size];
    for (int i = 0; i <= top; i++)
      pMem[i] = s.pMem[i];
  }
  ~TStack()
  {
    delete [] pMem;
  }
  TStack& operator=(const TStack &s)
  {
    if (this == &s)
      return *this;
    if (size != s.size)
    {
      T *p = new T[s.size];
      delete [] pMem;
      pMem = p;
      size = s.size;
    }
    top = s.top;
    for (int i = 0; i <= top; i++)
      pMem[i] = s.pMem[i];
    return *this;
  }
  bool IsEmpty() const
  {
    return top == -1;
  }
  bool IsFull() const
  {
    return top == size - 1;
  }
  int GetCount() const
  {
    return top + 1;
  }
  void Push(const T &val)
  {
    if (IsFull())
      throw std::overflow_error("Stack is full");
    top++;
    pMem[top] = val;
  }
  T Pop()
  {
    if (IsEmpty())
      throw std::underflow_error("Stack is empty");
    top--;
    return pMem[top + 1];
  }
  T Top() const
  {
    if (IsEmpty())
      throw std::underflow_error("Stack is empty");
    return pMem[top];
  }
  void Clear()
  {
    top = -1;
  }
};

#endif
