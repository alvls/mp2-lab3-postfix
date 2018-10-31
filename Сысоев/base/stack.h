#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
	T *pMem;
	int size;
	int top; // индекс последнего занятого в мем
public:
	TStack() :top(-1) {}
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
	bool IsEmpty() { //пуст ли стек
		return top == -1;
	}
	bool IsFull() { //заполнена ли память
		return top == size - 1;
	}
	T Pop() { //берет элемент
		if (!IsEmpty())
			return pMem[--top];
	}
	void Push(T v) {//положить элемент
		if (IsFull())
			return;
		pMem[++top] = v;
	}

	T GetElement()
	{
		return *(pMem + top);
	}
};

#endif
