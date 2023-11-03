#ifndef __STACK_H__
#define __STACK_H__

using namespace std;
const int MaxStackSize = 100;

template <class T>
class TStack
{
  T *pMem;                // стек
  size_t size;            // размер стека
  size_t top;             // вершина стека
public:
  friend class TPostfix;
  TStack(size_t _size);   // конструктор-инициализатор
  ~TStack();              // деструктор
  void empty();           // нет элементов
  size_t getSize() const; // получить размер стека
  T getTop() const;       // получить верхний элемент
  void push(T val);       // поместить в стек
  T pop();                // извлечь из стека
  
};

template <class T>
TStack<T>::~TStack()
{
    delete[] pMem;
}

template <class T>
TStack<T>::TStack(size_t _size)
{
    size = _size;
    top = 0;
    if ((size < 1) || (size > MaxStackSize))
        throw invalid_argument("invalid size");
    pMem = new T[size]();
}

template <class T>
void TStack<T>::empty() { return top == 0; }

template <class T>
size_t TStack<T>:: getSize() const { return size; }

template <class T>
T TStack<T>:: getTop() const
{
    if (top <= 0)
        throw exception("stack is empty");
    return(pMem[top - 1]);
}

template <class T>
void TStack<T>::push(T val)
{
    if (top >= size)
        throw exception("stack is full");
    pMem[top++] = val;
}

template <class T>
T TStack<T>::pop()
{
    if (top <= 0)
        throw exception("stack is empty");
    return pMem[--top];
}

#endif
