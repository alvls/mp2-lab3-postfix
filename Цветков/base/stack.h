#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
    T* pMem;
    int size;
    int top;
public:
    TStack(int _size = 10);
    TStack(const TStack<T>& s);
    ~TStack();
    void add(T tmp);
    T gettop();
    T infotop();
    bool empty();
    bool full();
    void setsize(int s);
    int getsize();
};
template <class T>
TStack<T>::TStack(const TStack<T>& s)
{
    size = s.size;
    pMem = new T[size];
    top = s.top;
    for (int i = 0; i <= top; i++)
        pMem[i] = s.pMem[i];
}
template <class T>
TStack<T>::TStack(int _size = 1)
{
    size = _size;
    top = -1;
    if ((size < 1) || (size > MaxStackSize))
        throw size;
    pMem = new T[size];
}
template <class T>
TStack<T>:: ~TStack()
{
    delete[] pMem;
}
template <class T>
void TStack<T>::add(T tmp)
{
    if (top + 1 >= size)
        throw size;
    pMem[++top] = tmp;
}
template <class T>
T TStack<T>::gettop()
{
    if (empty() == true)
    {
        throw 0;
    }
    return (pMem[top--]);
}
template <class T>
T TStack<T>::infotop()
{
    if (empty() == true)
    {
        throw 0;
    }
    return (pMem[top]);
}
template <class T>
bool TStack<T>::empty()
{
    if (top == -1)
        return true;
}
template <class T>
bool TStack<T>::full()
{
    if (top == size - 1)
        return true;
}
template <class T>
void TStack<T>::setsize(int s)
{
    size = s;
    top = -1;
    if ((size < 1) || (size > MaxStackSize))
        throw size;
    delete[] pMem;
    pMem = new T[size];
}
template <class T>
int TStack<T>::getsize()
{
    return size;
}
#endif

