#ifndef __STACK_H__
#define __STACK_H__
#include <cstddef>
const int MaxStackSize = 100;//размер памяти, выделяемый по умолчанию, если при создании стека 
//явно не указано требуемое количество элементов памяти,


template <class T>
class TStack
{
    T* pMem; //указатель на память, выделенную для хранения стека
    int size; //размер выделенной памяти
    int top; //индекс элемента массива, в котором хранится последнее добавленное значение стека.
    int DataCount; // количество запомненных в стеке значений
public:
    TStack(int _size) {
        size = _size;
        top = 0;
        if ((size < 1) || (size > MaxStackSize)) { throw size; }
        DataCount = 0;
        pMem = new T[size];
    }
    //деструктор
    ~TStack(){ delete[] pMem;}
    TStack& operator=(const TStack& tstack);
    int GetNextIndex(int index); // получить следующий индекс
    int IsEmpty(void) const;
    int IsFull(void) const;
    void Put(const T& Val);// добавить значение 
    virtual T Get ( void ) ; // извлечь значение
    T Pop();
};


template<class T>
inline TStack<T>& TStack<T>::operator=(const TStack<T> &tstack){
    if (this == &tstack) { return *this;}
    pMem = tstack.pMem;
    return *this;
}

template<class T>
inline int TStack<T>::GetNextIndex(int index) { return ++index; }

template<class T>
inline int TStack<T>::IsEmpty(void) const { return(DataCount == 0);}

template<class T>
inline int TStack<T>::IsFull(void) const { return (DataCount == size); }


//Метод Put используется для записи в стек значения Val.Перед 
//обращением к этой функции необходимо проверять стек на полноту. - из методички

template<class T>
inline void TStack<T>::Put(const T& Val){ 
    if (IsFull()) { throw (DataCount); }
    pMem[top] = Val;
    DataCount++;
    top++;
}

//Метод Get обеспечивает получение значения, записанного в стек последним; выполнение
//операции выполняется с удалением возвращаемого значения из стека.Перед обращением к 
//этой функции необходимо проверять стек на пустоту.Метод объявлен как виртуальный для
//последующей реализации схемы наследования.

template<class T>
inline T TStack<T>::Pop() {
    if (this->IsEmpty()) { throw exception(); }
    top--;
    DataCount--;
    T tmp = pMem[top];
    pMem[top] = NULL;
    return tmp;
}

template<class T>
inline T TStack<T>::Get(void) {
    if (IsEmpty()) { throw (top); }
    return pMem[top - 1];
}

#endif