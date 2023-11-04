#ifndef __STACK_H__
#define __STACK_H__

using namespace std;

template <class T>
class TStack {
	int top;
	size_t memSize;
	T* pMem;
public:
	TStack()
	{
		top = -1;
		memSize = 1;
		pMem = new T[memSize];
	}

	T Pop()
	{
		if (top < 0)
			throw "Stack is empty";
		return pMem[top--];
	}

	T Peek() const
	{
		if (top < 0)
			throw "Stack is empty";
		return pMem[top];
	}

	void Push(const T& val)
	{
		if (top == memSize - 1)
		{
			memSize *= 2;
			T* newMem = new T[memSize];
			copy(pMem, pMem + top + 1, newMem);
			delete[] pMem;
			pMem = newMem;
		}
		pMem[++top] = val;
	}

	TStack(const TStack& other) : top(other.top), memSize(other.memSize), pMem(new T[other.memSize])
	{
		copy(other.pMem, other.pMem + top + 1, pMem);
	}
	TStack& operator=(TStack other)
	{
		swap(*this, other);
		return *this;
	}
	friend void swap(TStack& first, TStack& second)
	{
		swap(first.top, second.top);
		swap(first.memSize, second.memSize);
		swap(first.pMem, second.pMem);
	}


	~TStack() { delete[] pMem; }

	size_t getSize() const { return top + 1; }

	bool IsEmpty() const { return top == -1; }
};

#endif