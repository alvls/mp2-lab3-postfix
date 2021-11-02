#ifndef __STACK_H__
#define __STACK_H__

#include <iostream>

using namespace std;

const int MaxStackSize = 100;

template <class T>
class TStack
{
    T* pMem;
    int size;
    int top;
public:
    //конструкторы 
    TStack(int _size)
    {
        size = _size;
        top = 0;
        if ((size < 1) || (size > MaxStackSize))
            throw size;
        pMem = new T[size];
    }
    //деструктор
    ~TStack()
    {
        if (pMem != NULL)
            delete[] pMem;
        pMem = NULL;
    }
    //методы
    bool isEmpty() const // контроль пустоты
    {
        return (top == 0);
    }
    bool isFull() const // контроль переполнения
    {
        //return top == size-1;
        return (top == size); //
    }
    void push(const T& val)
    {
        if (isFull())
            throw (top);
        pMem[top] = val;
        top++;
    }
    T Pop() // извлечь значение
    {
        if (this->isEmpty())
            throw exception();
        top--;
        T tmp = pMem[top];
        pMem[top] = NULL;//T();//T{};
        return tmp;
    }
    T Top()
    {
        if (isEmpty())
            throw (top);
        return pMem[top - 1];
    }
};

#endif