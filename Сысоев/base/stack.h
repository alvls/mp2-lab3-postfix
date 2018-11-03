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
	/*TStack<T>::TStack(const TStack<T> &_TStack) //Конструктор копирования.
	{
		size = _TStack.size;
		top = _TStack.top;
		pMem = new T[size];
	}
	TStack<T>& TStack<T>::operator=(const TStack<T> &_TStack)//оператор присваивания
	{
		if (this == &_TStack)
			return*this;
		if (size != _TStack.size)
		{
			size = _TStack.size;
			delete[]pMem;
			pMem = new T[size];
		}
		top = _TStack;
		for (int i = 0; i < size; i++)
			pMem[i] = _TStack.pMem[i];
		return *this;
	*/
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
			return pMem[top--];

	}
	void Push(T v) {//положить элемент
		if (IsFull())
			return;
		pMem[++top] = v;
	}

	T GetElement()
	{
		return pMem[top];
	}


	int lenght() //элементов в стэке в момент времени t.
	{
		return top + 1;
	}

	void Erase()//удалить последний
	{
		if (!IsEmpty())
			top--;
	}
};

#endif