
#ifndef __STACK_H__
#define __STACK_H__
#include <iostream>

const int MAX_STACK_SIZE  = 100000;
using namespace std;


template <class T>
class TStack
{
  int size;
  int top;
  T *stck;

  void reloadMemory(int mem = 10);
  bool isFull();
public:
	TStack(int _size);
	~TStack();
	int getSize(){return size;}
	int getTop(){return top;}
	T getTopElem(){if(isEmpty()) throw "Stack is empty" ; else return stck[top];}
	bool isEmpty();
	void push(T elem);
	T pop();
	friend ostream& operator<<(ostream &out, TStack& s)
	{
		for (int i = 0; i < s.getSize(); i++)
			out << s.stck[i] << ' ';
		return out;
	}
	
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
	if(isFull()) reloadMemory();  //throw "Stack overflow";
	stck[++top] = elem;
}

template<class T>
T TStack<T>::pop(){
	if(isEmpty()) throw "Stack is empty";
	return stck[top--];
}

template<class T>
void TStack<T>::reloadMemory(int mem  ) // на сколько эллементов увеличить 
{
	T *rep = new T[size];                   //записываем содержимое стека в массив 							
	for(int i = 0; i < size;i++)					
		rep[i] = stck[i];

	delete[] stck;                          // перевыделяем память 
	size += mem;
	stck = new T[size];

	for(int i = 0; i < size - mem;i++)      // заполняем стек 
		stck[i] = rep[i];


}





#endif