#ifndef __STACK_H__
#define __STACK_H__

#include <stdexcept>
#include <cstddef>

const int MaxStackSize = 100;

template <class T>
class TStack
{
  T *pMem;
  int size;
  int topIndex;
public:
  TStack(int _size = 50)
  {
    if ((_size < 1) || (_size > MaxStackSize))
      throw std::invalid_argument("Invalid stack size");
    size = _size;
    topIndex = -1;
    pMem = new T[size];
  }

  TStack(const TStack& other)
  {
    size = other.size;
    topIndex = other.topIndex;
    pMem = new T[size];
    for (int i = 0; i <= topIndex; i++) {
      pMem[i] = other.pMem[i];
    }
  }

  TStack& operator=(const TStack& other)
  {
    if (this != &other) {
      delete[] pMem;
      size = other.size;
      topIndex = other.topIndex;
      pMem = new T[size];
      for (int i = 0; i <= topIndex; i++) {
        pMem[i] = other.pMem[i];
      }
    }
    return *this;
  }

  ~TStack()
  {
    delete [] pMem;
  }

  bool empty() const
  {
    return topIndex == -1;
  }

  bool full() const
  {
    return topIndex == size - 1;
  }

  void push(const T& val)
  {
    if (full())
      throw std::out_of_range("Stack overflow");
    pMem[++topIndex] = val;
  }

  T pop()
  {
    if (empty())
      throw std::out_of_range("Stack is empty");
    return pMem[topIndex--];
  }

  T top() const
  {
    if (empty())
      throw std::out_of_range("Stack is empty");
    return pMem[topIndex];
  }
};

#endif