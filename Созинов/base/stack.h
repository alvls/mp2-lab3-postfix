#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
	T* pMem;
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
		delete[] pMem;
	}



	bool IsEmpty();//stack is Empty?
	bool IsFull();//stack is full?
	T Pop();//return from stack+
	void Push(const T Pval);//add to stack+
	T GetTopElem();//Get elem+
};


template <class T>
bool TStack<T>::IsEmpty()
{
	return (top == -1);
}

template <class T>
bool TStack<T>::IsFull()
{
	return (top == size - 1);
}

template <class T>
T TStack<T>::Pop()
{
	if (IsEmpty())
	{
		throw "Stack is Empty";

	}
	else
	{
		return pMem[top--];
	}
}

template <class T>
void TStack<T>::Push(const T Pval)
{
	if (IsFull())
	{
		throw "Stack is Full";

	}
	else
	{
		pMem[++top] = Pval;
	}
}

template <class T>
T TStack<T>::GetTopElem()
{
	if (this->IsEmpty())
	{
		throw "Stack is Empty";
	}
	else
	{
		return pMem[top];
	}
}

#endif
