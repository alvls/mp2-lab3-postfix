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
  ~TStack()
  {
    delete [] pMem;
  }
  void Put(const T &elem)
  {
	  if (top < size)
		  pMem[top++] = elem;
	  else
		  throw size;
  }
  T Get()
  {
	  if (top < 0)
		  throw top;
	  else
	  {
		  T elem;
		  elem = pMem[top];
		  pMem[--top];
		  return elem;
	  }
  }
  bool IsEmpty()
  {
	  for (int i = 0; i < size; i++)
	  {
		  if (pMem[i] != 0)
			  return false;
	  }
	  return true;
  }
  bool IsFull()
  {
	  for (int i = 0; i < size; i++)
	  {
		  if (pMem[i] == 0)
			  return false;
	  }
	  return true;
  }
};

#endif
