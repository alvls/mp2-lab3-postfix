#ifndef STACK_H
#define STACK_H
#include <stdexcept>
const int MaxStackSize = 1000;
template <class T>
class TStack
{
    T* pMem;
    int size;
    int top;
public:
    TStack(int _size)
    {
        size = _size;
        top = -1;
        if ((size < 1) || (size > MaxStackSize))
            throw std::runtime_error("Недопустимый размер стека");
        pMem = new T[size];
    }
    TStack(const TStack& st)
    {
        size = st.size;
        top = st.top;
        pMem = new T[size];
        for (int i = 0; i <= top; i++)
            pMem[i] = st.pMem[i];
    }

    ~TStack()
    {
        delete[] pMem;
    }

    bool IsEmpty() const { return top == -1; }
    bool IsFull() const { return top == size - 1; }

    void Push(const T& val)
    {
        if (IsFull())
            throw std::runtime_error("Стек переполнен");
        pMem[++top] = val;
    }

    T Pop()
    {
        if (IsEmpty())
            throw std::runtime_error("Стек пуст");
        return pMem[top--];
    }

    // Заменили Top() на Peek()
    T Peek() const
    {
        if (IsEmpty())
            throw std::runtime_error("Стек пуст");
        return pMem[top];
    }
};
#endif