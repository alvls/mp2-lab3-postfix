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
  TStack(int _size);
  ~TStack();
  TStack(const TStack& st);
  T GetTopElem();
  T Pop();
  void Push(T elem);
  bool Empty();
  bool Full();
};


template <class T>
TStack<T>::TStack(int _size) 
{
	size = _size;
	top = -1;
	if ((size < 1) || (size > MaxStackSize))
		throw "Wrong stack's size";
	pMem = new T[size];
}

template <class T>
TStack<T>::TStack(const TStack& st)
{
	pMem = new T[st.size];
	size = st.size;
	top = st.top;
	for (int i = 0; i < st.size; i++)
		pMem[i] = st.pMem[i];
}

template <class T>
TStack<T>::~TStack()
{
	delete[] pMem;
}

template <class T>
T TStack<T>::GetTopElem()
{
	return pMem[top];
}

template<class T>
T TStack<T>::Pop() 
{
	if (Empty())
		throw "Stack is empty";
	else
		return pMem[top--];
}

template <class T>
void TStack<T>::Push( T elem) 
{
	if (!(Full()))
		pMem[++top] = elem;
	else
		throw "Stack is full";
}

template <class T>
bool TStack<T>::Empty() 
{
	if (top == -1)
		return true;
	else
		return false;
}

template <class T>
bool TStack<T>::Full()
{
	if (top == size-1)
		return true;
	else
		return false;
}
#endif

