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
      throw std::invalid_argument("Invalid stack size");
    pMem = new T[size];
  }

  TStack(const TStack& other)
  {
    size = other.size;
    top = other.top;
    pMem = new T[size];
    for (int i = 0; i <= top; ++i)
    {
      pMem[i] = other.pMem[i];
    }
  }

  TStack& operator=(const TStack& other)
  {
    if (this != &other)
    {
      delete[] pMem;
      
      size = other.size;
      top = other.top;
      pMem = new T[size];
      
      for (int i = 0; i <= top; ++i)
      {
        pMem[i] = other.pMem[i];
      }
    }
    return *this;
  }

  ~TStack()
  {
    delete[] pMem;
  }

  bool IsEmpty() const
  {
    return top == -1;
  }

  void Push(const T& val)
  {
    if (top >= size - 1)
      throw std::overflow_error("Stack overflow");
    
    pMem[++top] = val;
  }

  T Pop()
  {
    if (IsEmpty())
      throw std::out_of_range("Stack is empty");
    
    return pMem[top--];
  }

  T& Top()
  {
    if (IsEmpty())
      throw std::out_of_range("Stack is empty");
    
    return pMem[top];
  }
};

#endif