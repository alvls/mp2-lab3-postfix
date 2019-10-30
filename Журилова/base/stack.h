#ifndef __STACK_H__
#define __STACK_H__
#include <iostream>
const int MaxStackSize = 100;

template <class T>
class TStack
{
private:
  T *pMem;
  int size;
  int top;
  TStack(const TStack &st) {}//Запрет на создание копии стека
  TStack& operator=(const TStack &st) {}//Запрет на присваивание 
public:
	//Конструктор
  TStack(int _size)
  {	  
	 size = _size;
	 top = -1;  
	 if ((size < 1) || (size > MaxStackSize))
	 {
		 throw "Error with Stack's size";
	 }
    pMem = new T[size];
  }
  //Проверка на пустоту стека
  bool empty()
  {
	  if (top == (-1))//Стек пуст
		  return true;
	  else
		  return false;
  }
  //Проверка на полноту стека
  bool full()
  {
	  if (top == (size - 1))//Стек заполнен
		  return true;
	  else
		  return false;
  }
  //Взять элемент из стека
  T pop()
  {
	  if (empty() == true)//Проверка на пустоту стека
	  {
		  throw "Error witn POP";
	  }
	  return pMem[top--];//Вернуть pMem[top] и top--
  }
  //Положить элемент в стека
  void push(T Elem)
  {
	  if (full() == true)//Проверка на заполненность стека
	  {
		  throw "Error witn PUSH";
	  }
	  pMem[++top] = Elem;//Увеличили top на 1 и положили элемент в pMem
  }
  //Деструктор
  ~TStack()
  {
    delete [] pMem;
  }
};

#endif
