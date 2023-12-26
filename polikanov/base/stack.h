#ifndef __STACK_H__
#define __STACK_H__

#include <string>

const int MaxStackSize = 100;

template <class TType>
class TStack {
private:
	TType* pMem;
	int size;
	int top;
	TStack(const TStack&) = delete;
	void operator=(const TStack&) = delete;

public:
	TStack(int _size = MaxStackSize) {
		size = _size;
		top = -1;
		if ((size < 1) || (size > MaxStackSize))
			throw std::invalid_argument("Неверная длина стека");
		pMem = new TType[size];
	}

	~TStack() {
		delete[] pMem;
	}

	bool empty() { return top == -1; }

	bool full() { return top == size - 1; }

	void push(const TType obj) {
		if (full())
			throw std::length_error("Стек заполнен");
		pMem[++top] = obj;
	}

	TType pop() {
		if (empty())
			throw std::length_error("Стек пуст");
		return pMem[top--];
	}

	TType peek() {
		if (empty())
			throw std::length_error("Стек пуст");
		return pMem[top];
	}
};

#endif