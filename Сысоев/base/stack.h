#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
  T *pMem;
  int size;
  int top;  //индекс последнего элемента в pMem
public:
  TStack(int _size)
  {
    size = _size;
    top = -1;
    if ((size < 1) || (size > MaxStackSize))
      throw size;
    pMem = new T[size];
  }

  //TStack(): top(-1){}
  ~TStack()
  {
    delete [] pMem;
  }

  bool IsEmpty() {                            //проверить стек на пустоту
	  return top == -1;
  }
  bool IsFull() {
	  return top == size - 1;                //проверить стек на полноту
  }
  char Pop() {                                   //взять из стека(элемент пропадает)
	  if (!IsEmpty())
		  return pMem[top--];
  }
  void Push(double v) {                            //добавить элемент
	  if (IsFull())
		  return pMem[++top] = v;
  }

  char Back()
  {
	  if (IsEmpty())
		  throw "Error";
	  return pMem[top];
  }

 /* TStack GetElement()                        //посмотреть элемент
  {
	  return pMem[top];
  }*/
  int GetLenght()                                 //количество элементов в стеке
  {
	  return top + 1;
  }
  void Remove()                                 //удалить последний
  {
	  if (!IsEmpty())
		  top--;
  }
};

#endif
