#ifndef STACK_H
#define STACK_H

using namespace std;

template <class T>
class TStack
{
	int top;
	size_t size;
	T* pMem;
public:
	TStack() : top(-1), size(1), pMem(new T[size]) {}
	~TStack()
	{
		delete[] pMem;
	}
	size_t GetSize() const { return top + 1; }
	bool IsEmpty() const { return top == -1; }
	T Pop()
	{
		if (top < 0)
			throw "stack is empty";
		return pMem[top--];
	}
	void Push(const T& val)
	{
		if (top == size - 1)
		{
			size *= 2;
			T* tmp = new T[size];
			copy(pMem, pMem + size, tmp);
			delete[] pMem;
			pMem = tmp;
		}
		pMem[++top] = val;
	}
};
#endif