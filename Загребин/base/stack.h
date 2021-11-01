#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
  T *pMem;
  int size;
  int top;// index (real size)
public:
  TStack(int _size = 5){
    if ((_size < 1) || (_size > MaxStackSize))
        throw -1;
    size = _size;
    top = -1;
    pMem = new T[size];
  }
  bool Empty() {
      return top == -1;
  }
  void push(T elem) {
      T* buff; int _size;
      if (top == size - 1) {
          if (size < 50)
              _size = size << 1;
          else if (size != 100)
              _size = 100;
          else
              throw -1;
          buff = new T[_size];
          std::copy(pMem, pMem + size, buff);
          delete[] pMem; pMem = buff; size = _size;
      }
      pMem[++top] = elem;
  }
  T& Top() {
      if (top == -1)
          throw -1;
      return pMem[top];
  }
  T pop() {
      if (top == -1)
          throw -1;
      return pMem[top--];
  }
  int GetSize() {
      return top+1;
  }
  ~TStack(){
    delete [] pMem;
  }
};

#endif
