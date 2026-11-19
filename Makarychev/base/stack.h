#ifndef __STACK_H__
#define __STACK_H__

#include <stdexcept>

const int MaxStackSize = 100;

template <class T>
class TStack
{
  T* pMem;
  int size;
  int top;
public:
  explicit TStack(int _size) : pMem(0), size(_size), top(-1)
  {
    if (size < 1 || size > MaxStackSize)
      throw std::out_of_range("Invalid stack size");
    pMem = new T[size];
  }

  TStack(const TStack& other) : pMem(new T[other.size]), size(other.size), top(other.top)
  {
    for (int i = 0; i <= top; ++i) pMem[i] = other.pMem[i];
  }

  TStack& operator=(const TStack& other)
  {
    if (this != &other)
    {
      T* memory = new T[other.size];
      for (int i = 0; i <= other.top; ++i) memory[i] = other.pMem[i];
      delete[] pMem;
      pMem = memory;
      size = other.size;
      top = other.top;
    }
    return *this;
  }

  ~TStack() { delete[] pMem; }

  bool IsEmpty() const { return top == -1; }
  bool IsFull() const { return top == size - 1; }
  int GetSize() const { return size; }
  int GetCount() const { return top + 1; }
  void Clear() { top = -1; }

  void Push(const T& value)
  {
    if (IsFull()) throw std::overflow_error("Stack overflow");
    pMem[++top] = value;
  }

  T Pop()
  {
    if (IsEmpty()) throw std::underflow_error("Stack underflow");
    return pMem[top--];
  }

  T Top() const
  {
    if (IsEmpty()) throw std::underflow_error("Stack is empty");
    return pMem[top];
  }
};

#endif
