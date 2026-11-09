#ifndef __STACK_H__
#define __STACK_H__

#include <stdexcept>

const int MaxStackSize = 100;

template <class T>
class TStack
{
    T* pMem;
    int size;
    int top;

public:
    TStack(int _size)
    {
        if (_size < 1 || _size > MaxStackSize)
            throw std::invalid_argument("TStack: invalid stack size");
        size = _size;
        top = -1;
        pMem = new T[size];
    }

    TStack(const TStack& other)
        : size(other.size), top(other.top), pMem(new T[other.size])
    {
        for (int i = 0; i <= top; ++i)
            pMem[i] = other.pMem[i];
    }

    TStack& operator=(const TStack& other)
    {
        if (this == &other) return *this;
        T* newMem = new T[other.size];
        for (int i = 0; i <= other.top; ++i)
            newMem[i] = other.pMem[i];
        delete[] pMem;
        pMem = newMem;
        size = other.size;
        top = other.top;
        return *this;
    }

    ~TStack() { delete[] pMem; }

    void Push(const T& value)
    {
        if (top + 1 >= size)
            throw std::overflow_error("TStack: stack overflow");
        pMem[++top] = value;
    }

    T Pop()
    {
        if (IsEmpty())
            throw std::underflow_error("TStack: stack is empty");
        return pMem[top--];
    }

    T& Top()
    {
        if (IsEmpty())
            throw std::underflow_error("TStack: stack is empty");
        return pMem[top];
    }

    const T& Top() const
    {
        if (IsEmpty())
            throw std::underflow_error("TStack: stack is empty");
        return pMem[top];
    }

    bool IsEmpty() const { return top == -1; }
    bool IsFull()  const { return top + 1 >= size; }
    int  GetSize() const { return size; }
    int  GetCount() const { return top + 1; }

    void Clear() { top = -1; }
};

#endif
