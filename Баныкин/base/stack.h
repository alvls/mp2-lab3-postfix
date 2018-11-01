#include <iostream>
#ifndef __STACK_H__
#define __STACK_H__
using namespace std;
const int MaxStackSize = 100;

template <class T>
class TStack {
	T *pMem;
	int size;//размер стека
	int top;//позиция последнего записанного элемента
public:
	TStack(int _size) {
		size = _size;
		top = -1;
		if ((size < 1) || (size > MaxStackSize))
			throw size;
		pMem = new T[size];
	}

	TStack<T> & operator=(const TStack<T> &s) {
		if (this == &s)
			return *this;
		if (size != s.size) {
			delete[] pMem;
			pMem = new T[s.size];
			size = s.size;
		}

		for (int i = 0; i < size; i++)
			this->pMem[i] = s.pMem[i];
		top = s.top;

		return *this;
	}

	bool operator==(const TStack &st) {
		if (size != st.size)
			return false;
		if (*this == &st)
			return true;
		for (int i = 0; i < size; ++i)
			if (pMem[i] != st.pMem[i])
				return false;
		return true;
	}

	int Size() {
		return size;
	}

	TStack(const TStack &s) {
		pMem = new T[s.size];
		size = s.size;
		top = s.top;

		for (int i = 0; i < size; i++)
			this->pMem[i] = s.pMem[i];
	}

	T look_top() {
		return pMem[top];
	}

	void push_back(T elem) {
		if (full())
			throw "Stack is full";
		pMem[++top] = elem;
	}

	T pop_back() {
		if (empty())
			throw "Stack is empty";
		return pMem[--top + 1];
	}

	bool empty() {
		return top == -1;
	}

	bool full() {
		return top == size - 1;
	}

	friend  ostream& operator<<(ostream &os, TStack<T> &st) {
		for (int i = 0; i <= st.top; i++)
			os << st.pMem[i] << endl;
		return os;
	}

	~TStack() {
		delete[] pMem;
	}

};

#endif