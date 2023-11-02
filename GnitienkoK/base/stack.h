#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

namespace tabl {
	static double a = 10.0;
	static double b = 20.0;
	static double c = 30.0;
}

template <class T>
class TStack
{
	T* pMem;
	size_t size;
	int top;
public:
	TStack():top(-1), size(MaxStackSize) {
		pMem = new T[size]();
	};
	TStack(int _size)
	{
		if ((_size < 1) || (_size > MaxStackSize))
			throw _size;
		size = _size;
		top = -1;
		pMem = new T[size]();
	}
	size_t ssize() const { return top + 1; }
	bool IsEmpty() const { return top == -1; }
	bool IsFull() const { return top == size - 1; }
	void push(const T& val) {
		if (top == size - 1) {
			T* tmpMem = new T[size * 2];
			std::copy(pMem, pMem + size, tmpMem);
			delete[] pMem;
			pMem = tmpMem;
			size *= 2;
		}
		pMem[++top] = val;
	}
	T Top() { return pMem[top]; }
	T pop() { return pMem[top--]; }
	~TStack()
	{
		delete[] pMem;
	}
};

#endif
