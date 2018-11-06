#ifndef __STACK_H__ 
#define __STACK_H__ 

const int MaxStackSize = 100;

template <class Telem>
class TStack
{
	Telem *pMem;
	int size;
	int top;
public:
	TStack(int _size)
	{
		size = _size;
		top = -1;
		if ((size < 1) || (size > MaxStackSize))
			throw size;
		pMem = new Telem[size];
	}
	~TStack()
	{
		delete[] pMem;
	}
	bool IsFull()
	{
		if (top == (size - 1))
			return true;
		return false;
	}
	bool IsEmpty()
	{
		if (top == -1)
			return true;
		return false;
	}
	void Push(const Telem &val)
	{
		if (IsFull() == false)
		{
			top++;
			pMem[top] = val;
		}
		else throw "error";
	}
	Telem Pop()
	{
		if (IsEmpty()  == false)
			return pMem[top--];
		else throw "error";
	}
	Telem Back()
	{
		return pMem[top];
	}
};

#endif