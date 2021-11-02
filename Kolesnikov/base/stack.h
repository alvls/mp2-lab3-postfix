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
  TStack(int _size)
  {
    size = _size;
    top = -1;
    if ((size < 1) || (size > MaxStackSize))
      throw size;
    pMem = new T[size];
  }
  bool IsFull() const
  {
    return top == size-1;
  }
  int GetSize() const
  {
    return top + 1;
  }
  bool IsEmpty() const
  {
    return top == -1;
  }
  void Push(const T& item)
  {
    if(IsFull())
      throw "Stack is full";
    top++;
    pMem[top] = item;
    return;
  }
  T PopTop() 
  {
    if(IsEmpty())
      throw "Stack is empty";
    return pMem[top--];
  }
  T Top() const 
  {
    if(IsEmpty())
      throw "Stack is empty";
    return pMem[top];
  }
  ~TStack()
  {
    delete [] pMem;
  }
};

#endif
