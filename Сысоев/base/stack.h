#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack 
{
  T *pMem;
  int size;
  int top;//индекс последнего элемента стека
public:
  TStack(int _size=1)
  {
    size = _size;
    top = -1;
    if ((size < 1) || (size > MaxStackSize))
      throw size;
    pMem = new T[size];
  }
  ~TStack()
  {
    delete [] pMem;
  }
  /*TStack<T>& operator=(const TStack<T>& st)
  {
      if (this == &st)
          return (*this);
      if ((st.size < 1) || (st.size > MaxStackSize))
          throw size;
      if (size != st.size)
      {
          T* tmp = new T[st.size];
          size = st.size;
          for (int i = 0; i < size; i++)
          {
              tmp[i] = pMem[i];
          }
          delete[]pMem;
          pMem = tmp;
          delete[]tmp;
      }
      else 
          if (size == st.size)
          {
              for (int i = 0; i < size; i++)
              {
                  pMem[i] = st.pMem[i];
              }
          }
      top=st.top;
      return(*this);
  }*/
  void push(T elem)
  {
     /* if (top == (size - 1))//перевыделение памяти
      {
          size++;
          T* tmp = pMem;
          delete[] pMem;
          pMem = new T[size];
          for (int i = 0; i < (size - 1); i++)
              pMem[i] = tmp[i];
          //pMem[size - 1] = elem;
      }*/
      top ++;
      pMem[top] = elem;
  }
  
  T pop()
  {
      T res;
      if (top >= 0)
      {
          res = pMem[top];
          top--;
      }
      else
          throw "invalid top index";
      return (res);
  }
  int get_size()
  {
      return (top+1);
  }
  bool isfull()
  {
      return (top >= 0);                     // истина если стек  полон, ложь в противном случае   
  }
  bool isempty()
  {
      return (top < 0);                     // истина если стек  пуст, ложь в противном случае   
  }
};

#endif
