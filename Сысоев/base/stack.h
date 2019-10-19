#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
  T *pMem;
  int size;
  int top;
public:
	TStack(int _size);
	~TStack();
	bool IsEmpty();
	bool IsFull();
	void Push(T val);
	T pop();
	T GetTop();

};

template <class T>
TStack<T>::TStack(int _size) {
		size = _size;
		top = -1;
		if ((size < 1) || (size > MaxStackSize))
			throw size;
		pMem = new T[size];	
}

template <class T>
TStack<T>::~TStack()
{
	delete[] pMem;
}

template <class T>
bool TStack<T>::IsEmpty() {
	return top == -1;
}
template <class T>
bool TStack<T>::IsFull() {
	return top == size - 1;
}

template <class T>
void TStack<T>::Push(T val) {
	if (IsFull())
		throw val;
	pMem[++top] = val;
}
template <class T>
T TStack<T>::pop() {
	if (IsEmpty())
		throw "Error";
	return pMem[top--];
}
template <class T>
T TStack<T>::GetTop() {
	return pMem[top];
}
#endif
        