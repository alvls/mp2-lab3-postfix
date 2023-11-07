#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
  T* pMem;
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
    delete[] pMem;
  }
  bool IsEmpty() const
  {
    return top == -1;
  }
  bool IsFull() const
  {
    return top == size - 1;
  }
  void Push(const T& item)
  {
    if (IsFull())
      throw "Stack full";
    pMem[++top] = item;
  }
  T Pop()
  {
    if (IsEmpty())
      throw "Stack empty";
    return pMem[top--];
  }
  T Peek() const
  {
    if (IsEmpty())
      throw "Stack empty";
    return pMem[top];
  }
};

#endif __STACK_H__