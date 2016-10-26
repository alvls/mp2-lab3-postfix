#ifndef __STACK_H__
#define __STACK_H__

const int MAX_STACK_SIZE  = 100000000;

template <class T>
class TStack
{
  int size;
  int top;
  T *stck;
  
public:
	TStack(int _size);
	~TStack();
	bool isFull();
	bool isEmpty();
	void push(T elem);
	T pop();
	void reloadMemory();
};
template<class T>
TStack<T>::TStack(int _size)
{
	if(_size > MAX_STACK_SIZE || _size <= 0 ) throw"Invalid size in TStack(int _size)";
	size = _size;
	stck = new T[size];
	top = -1;
}

template<class T>
TStack<T>::~TStack()
{
	delete[] stck;
}

template<class T>
bool TStack<T>::isFull(){
	return top == size - 1;
}

template<class T>
bool TStack<T>::isEmpty(){
	return top == -1;
}

template<class T>
void TStack<T>::push(T elem){
	if(isFull()) throw "Stack overflow"; // reloadMemory();
	stck[++top] = elem;
}

template<class T>
T TStack<T>::pop(){
	if(isEmpty()) throw "Stack is empty";
	return stck[top--];
}





#endif
