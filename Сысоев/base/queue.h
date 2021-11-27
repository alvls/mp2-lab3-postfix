#ifndef __QUEUE_H__
#define __QUEUE_H__
#include <iostream>
const int MaxQueueSize = 16;
enum class ans
{
    negative = -1,
    empty,
    too_large,
};
template <class T>
class Tqueue
{
protected:
    T* pMem;
    int Size;
    int begin;//[begin; end)
    int end;//[begin;end)
public:
    Tqueue();
    Tqueue(const Tqueue& q);
    ~Tqueue();
    Tqueue& operator=(const Tqueue& q);
    int size() { return Size; }
    void push(const T& obj);
    T get() const;
    T pop();
    bool is_empty() const;
    bool is_full() const;
    const T& operator[](int pos) const;
};

template<class T> 
Tqueue<T>::Tqueue():Size(0),begin(0),end(0)
{
    pMem = new T[MaxQueueSize];
}
template<class T> 
Tqueue<T>::Tqueue(const Tqueue& q) :Size(q.Size),begin(q.begin),end(q.end)
{
    pMem = new T[MaxQueueSize];
    std::copy(q.pMem, q.pMem + MaxQueueSize, pMem);
}
template<class T>
Tqueue<T>&Tqueue<T>::operator=(const Tqueue& q)
{
    Size = q.Size;
    begin = q.begin;
    end = q.end;
    std::copy(q.pMem, q.pMem + MaxQueueSize, pMem);
}
template<class T>
Tqueue<T>::~Tqueue()
{
    delete[] pMem;
}
//Вставка в конец
template<class T> 
void Tqueue<T>::push(const T& obj)
{
    if (is_full())
        throw ans::too_large;
    pMem[end] = obj;
    end = (end + 1) % MaxQueueSize;
    Size++;
}
//Изъятие из начала без удаления
template <class T> 
T Tqueue<T>::get() const
{
    if (is_empty())
        throw ans::empty;
    return pMem[begin];
}
//Изъятие из начала с удалением
template <class T>
T Tqueue<T>::pop()
{
    if (is_empty())
        throw ans::empty;
    T tmp = pMem[begin];
    begin = (begin + 1) % MaxQueueSize;
    Size--;
    return tmp;
}
template <class T> 
const T& Tqueue<T>::operator[](int pos) const
{
    if (pos < 0)
        throw ans::negative;
    if (pos >= Size)
        throw ans::too_large;
    return pMem[(pos + begin) % MaxQueueSize];
}
template<class T> 
bool Tqueue<T>::is_empty() const
{
    if (Size > 0)
        return false;
    else
        return true;
}
template<class T> 
bool Tqueue<T>::is_full() const
{
    if (Size < MaxQueueSize)
        return false;
    else
        return true;
}
#endif
