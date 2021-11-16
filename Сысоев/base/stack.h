#ifndef __STACK_H__
#define __STACK_H__
#include <iostream>
#include <locale>
const int MaxStackSize = 100;
enum class ans
{
    negative = -1,
    empty,
    too_large,
};
template <class T>
class TStack
{
protected:
    T* pMem;
    int size;
public:
    TStack& operator=(const TStack& stack);
    TStack(int _size = 0);
    TStack(TStack& stack);
    ~TStack();
    int getsize() { return size; }
    void put(const T& obj);
    T get();
    const T& top_of_stack() const;
    bool is_empty() const;
    bool is_full() const;
    const T& operator[](int pos) const;
};

template<class T>
TStack<T>& TStack<T>::operator=(const TStack& stack)
{
    size = stack.size;
    for (int i = 0; i < size; i++)
        pMem[i] = stack[i];
    return *this;
}
template<class T> 
TStack<T>::TStack(int _size)
{
    if (_size < 0)
        throw ans::negative;
    if (_size > MaxStackSize)
        throw ans::too_large;
    size = _size;
    pMem = new T[MaxStackSize];
}
template<class T> 
TStack<T>::TStack(TStack& stack) :size(stack.size)
{
    pMem = new T[size];
    std::copy(stack.pMem, stack.pMem + size, pMem);
}
template<class T>
TStack<T>::~TStack()
{
    //if (!is_empty())
        delete[] pMem;
}
template<class T> 
void TStack<T>::put(const T& obj)
{
    if (is_full())
        throw ans::too_large;
    pMem[size] = obj;
    size++;
}
template <class T> 
T TStack<T>::get()
{
    if (is_empty())
        throw ans::empty;
    T tmp = top_of_stack();
    size--;
    return tmp;
}
template <class T> 
const T& TStack<T>::operator[](int pos) const
{
    if (pos < 0)
        throw ans::negative;
    if (pos >= size)
        throw ans::too_large;
    return pMem[pos];
}
template<class T> 
bool TStack<T>::is_empty() const
{
    if (size > 0)
        return false;
    else
        return true;
}
template<class T> 
bool TStack<T>::is_full() const
{
    if (size < MaxStackSize)
        return false;
    else
        return true;
}
template<class T> 
const T& TStack<T>::top_of_stack() const
{
    return pMem[size - 1];
}
#endif
