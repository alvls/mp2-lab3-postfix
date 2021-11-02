#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

enum Errors
{
    stackOverFlow,
    stackIsEmpty,
    errorSize
};

template <class T>
class TStack
{
  T *pMem;
  int size; //размер стека
  int top; //индекс верхнего элемента стека
public:
  TStack(int _size = MaxStackSize) : size(_size) , top(-1)
  {
      if ((size < 1) || (size > MaxStackSize))
          throw errorSize;
      pMem = new T[size];
  }
  ~TStack()
  {
    delete [] pMem;
  }
  TStack(const TStack& otherStack) : size(otherStack.size), top(otherStack.top)
  {
      pMem = new T[size];
      for (size_t i = 0; i < size; i++)
      {
          pMem[i] = otherStack.pMem[i];
      }
  }

  bool isEmpty();
  bool isFull();
  void Push(const T& value);
  T Pop();
  T GetTopElem();
  int GetSize();
  int GetTopIndex();

  TStack& operator=(const TStack& otherStack);
  bool operator==(const TStack& otherStack) const;
  bool operator!=(const TStack& otherStack) const;
};


template<class T>
inline bool TStack<T>::isEmpty()
{
    return top == -1;
}

template<class T>
inline bool TStack<T>::isFull()
{
    return top == size - 1;
}

template<class T>
inline int TStack<T>::GetSize()
{
    return size;
}

template<class T>
inline int TStack<T>::GetTopIndex()
{
    return top;
}

template<class T>
inline TStack<T>& TStack<T>::operator=(const TStack& otherStack)
{
    if (this == &otherStack)
        return *this;
    else
    {
        T* temp = new T[otherStack.size];
        size = otherStack.size;
        top = otherStack.top;
        delete[] pMem;
        pMem = temp;
        for (size_t i = 0; i < size; i++)
        {
            pMem[i] = otherStack.pMem[i];
        }
        return *this;
    }
}

template<class T>
inline bool TStack<T>::operator==(const TStack& otherStack) const
{
    if (size != otherStack.size || top != otherStack.top)
        return false;
    for (size_t i = 0; i < size; i++)
    {
        if (pMem[i] != otherStack.pMem[i])
            return false;
    }
    return true;
}

template<class T>
inline bool TStack<T>::operator!=(const TStack& otherStack) const
{
    return !(*this);
}

template<class T>
inline void TStack<T>::Push(const T& value)
{
    if (isFull())
        throw stackOverFlow;
    pMem[++top] = value;
}

template<class T>
inline T TStack<T>::Pop()
{
    if (isEmpty())
        throw stackIsEmpty;
    return pMem[top--];
}

template<class T>
inline T TStack<T>::GetTopElem()
{
    if (isEmpty())
        throw stackIsEmpty;
    return pMem[top];
}
#endif