#ifndef __STACK_H__
#define __STACK_H__

using namespace std;
const int MaxStackSize = 100;

template <class T>
class TStack
{
  T *pMem;     // стек
  size_t size; // размер стека
  size_t top;     // вершина стека
public:
    friend class TPostfix;
  TStack(size_t _size) // конструктор-инициализатор
  {
    size = _size;
    top = 0;
    if ((size < 1) || (size > MaxStackSize))
        throw invalid_argument("invalid size");
    pMem = new T[size]();
  }

  ~TStack() // деструктор
  {
    delete [] pMem;
  }

  size_t getSize() const { return size; } // получить размер стека

  T getTop() const // получить верхний элемент
  {
      if (top <= 0)
          throw exception("stack is empty");
      return(pMem[top - 1]);
  }

  void push(T val) // поместить в стек
  {
      if (top >= size)
          throw exception("stack is full");
      pMem[top++] = val;
  }

  T pop() // извлечь из стека
  {
      if (top <= 0)
          throw exception("stack is empty");
      return pMem[--top];
  }
};

#endif
