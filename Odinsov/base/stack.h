#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
  T *pMem;
  size_t size;
  int top;
public:
  TStack(int _size=100)
  {
    size = _size;
    top = -1;
    if ((size < 1) || (size > MaxStackSize))
      throw size;
    pMem = new T[size];
  }
  bool isempty() {
      if (top == -1)
          return true;
      return false;
  }
  size_t getsize() { return size; }
  void Push(T value) {
      if (top+1 >= size)
          throw "No space for element";
      pMem[++top] = value;
  }
  T Pop() {
      if (isempty())
          throw "No element";
      return pMem[top--];
  }
  ~TStack()
  {
    delete [] pMem;
  }
};

#endif
