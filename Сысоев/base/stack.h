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
	void Push(T val);
	T Pop();
	bool IsEmpty();
	bool IsFull();
	T GetTop();
};

template <class T>
TStack<T>::TStack(int _size)
{
	if ((_size < 1) || (_size > MaxStackSize))
		throw "Wrong";
	size = _size;
	top = -1;
	pMem = new T[size];
}
template <class T>
TStack<T>::~TStack()
{
	delete[] pMem;
}
template<class T>
void TStack<T>::Push(T val)
{
	if (IsFull()) 
		throw "Stack is full";
	pMem[++top] = val;
}
template<class T>
T TStack<T>::Pop()
{
	if (IsEmpty()) 
		throw "Stack is empty";
	return pMem[top--];
}
template<class T>
bool TStack<T>::IsEmpty()
{
	return top == -1;
}
template<class T>
bool TStack<T>::IsFull()
{
	return top == (size - 1);
}
template <class T>
T TStack<T>::GetTop() {
	return pMem[top];
}
#endif
