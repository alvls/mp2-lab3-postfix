
#ifndef __STACK_H__
#define __STACK_H__

using namespace std;
const int MaxStackSize = 129;

template <class T>
class TStack
{
    T* pMem;                                    // стек
    size_t size;                                // размер стека
    size_t top;                                 // вершина стека
public:                                         
    friend class TPostfix;                      
    TStack();                                   // конструктор-инициализатор
    TStack(size_t _size);                       // конструктор-инициализатор
    TStack(const TStack<T>& st);                // конструктор копирования
    ~TStack();                                  // деструктор
    inline bool empty();                        // нет элементов
    size_t getSize() const noexcept;            // получить размер стека
    T getTop() const;                  // получить верхний элемент
    void push(T val);                           // поместить в стек
    T pop();                                    // извлечь из стека
    //------------------------------------------// операторы
    TStack<T>& operator=(const TStack<T>& st);  
    bool operator==(const TStack<T>& st) const;
    bool operator!=(const TStack<T>& st) const;
};

template <class T>
TStack<T>::~TStack() { delete[] pMem; }

template <class T>
TStack<T>::TStack() : TStack(8) {}

template <class T>
TStack<T>::TStack(size_t _size) : top(0), size(_size) 
{ 
    if (size >= MaxStackSize || size <= 0)
        throw invalid_argument("invalid stack size");
    pMem = new T[size](); 
}

template <class T>
TStack<T>::TStack(const TStack<T>& st) : top(st.top), size(st.top)
{
    pMem = new T[size]();
    copy(st.pMem, st.pMem + top, pMem);
}

template <class T>
bool TStack<T>::operator==(const TStack<T>& st) const
{
    if (st.pMem == pMem)
        return true;
    if (top != st.top)
        return false;
    for (size_t i = 0; i < top; i++)
        if (pMem[i] != st.pMem[i])
            return false;
    return true;
}

template <class T>
bool TStack<T>::operator!=(const TStack<T>& st) const { return !(*this == st); }

template <class T>
inline bool TStack<T>::empty() { return top == 0; }

template <class T>
size_t TStack<T>::getSize() const noexcept { return top; }

template <class T>
T TStack<T>::getTop() const 
{
    if (top <= 0)
        throw runtime_error("stack is empty");
    return(pMem[top - 1]);
}

template <class T>
void TStack<T>::push(T val)
{
    if (top >= size)
    {
        size *= 2;
        if (size > MaxStackSize)
            throw runtime_error("too large stack");
        T* tmp = new T[size];
        copy(pMem, pMem + top, tmp);
        delete[] pMem;
        pMem = tmp;
    }
    pMem[top++] = val;
}

template <class T>
T TStack<T>::pop()
{
    if (top <= 0)
        throw runtime_error("stack is empty");
    return pMem[--top];
}

template <class T>
TStack<T>& TStack<T>::operator=(const TStack<T>& st)
{
    if (pMem == st.pMem)
        return *this;
    else if (top == st.top)
        copy(st.pMem, st.pMem + top, pMem);
    else
    {
        try {
            top = st.top;
            T* tmp = new T[top];
            copy(st.pMem, st.pMem + top, tmp);
            delete[] pMem;
            pMem = tmp;
        }
        catch (...) {
            throw runtime_error("can't create stack");
        }
    }
    return *this;
}

#endif
