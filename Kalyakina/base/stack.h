#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
	int size;
	int top;
	T* pMem;
	TStack(const TStack&) = delete;
	void operator=(const TStack&) = delete;

public:
	TStack(int _size = MaxStackSize);
	T getTop();
	T pop();
	void push(T val);
	bool empty();
	~TStack();
};

template <class T>
TStack<T>::TStack(int _size) : size(_size), top(-1)
{
	if ((size < 1) || (size > MaxStackSize))
		throw "Size of stack is out of range";
	pMem = new T[size];
}

template <class T>
T TStack<T>::getTop()
{
	if (top < 0)
		throw "Stack is empty";
	return pMem[top];
}

template <class T>
T TStack<T>::pop()
{
	if (top < 0)
		throw "Stack is empty";
	return (pMem[top--]);
}

template <class T>
void TStack<T>::push(T val)
{
	if (top + 1 >= size)
		throw "Stack is full";
	pMem[++top] = val;
}

template <class T>
bool TStack<T>::empty()
{
	return (top == -1);
}

template <class T>
TStack<T>::~TStack()
{
	delete[] pMem;
}

#endif