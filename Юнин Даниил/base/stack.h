#ifndef __STACK_H__
#define __STACK_H__

#include <iostream>

using namespace std;

const int MaxStackSize = 100;//Максимальный размер памяти для стека (на 100 элементов)

template <class ValType>
class TStack {
private:
    //Поля
    ValType* pMem;//Указатель на память СД.
    int MemSize;//Размер памяти СД.
    int Top;//Индекс верхнего элемента.
    int DataCount;//Количество элементов в СД.
    //Методы
    int GetNextIndex(int index);
public:
    TStack(int _Size = MaxStackSize);
    TStack(const TStack& v);
    ~TStack();
    //int GetMemSize() { return MemSize; }
    int GetTop() { return Top; }                  //подумать нужно ли их реализовывать!
    int GetDataCount() { return DataCount; }
    bool IsEmpty(void) const;
    bool IsFull(void) const;
    void Put(const ValType& val);
    ValType Get(void);//Возвращать ссылку или нет?
    TStack& operator=(const TStack& val);
    void Print(void);
};

template <class ValType>//Возвращение следующего индекса.
int TStack<ValType>::GetNextIndex(int index) {
    return ++index;
}

template <class ValType>//Конструктор.
TStack<ValType>::TStack(int _Size = MaxStackSize) {
    MemSize = _Size;
    DataCount = 0;
    Top = -1;
    if ((MemSize < 1) || (MemSize > MaxStackSize))
        throw "invalid variable value.";
    pMem = new ValType[MemSize];
}

template <class ValType>
TStack<ValType>::~TStack() {
    delete[] pMem;
}

template <class ValType>
TStack<ValType>::TStack(const TStack& st) {
    MemSize = st.MemSize;
    DataCount = st.DataCount;
    Top = st.Top;
    pMem = new ValType[MemSize];
    for (int i = 0; i < MemSize; i++) {
        pMem[i] = st.pMem[i];
    }
}

template <class ValType>
bool TStack<ValType>::IsEmpty(void) const {
    return DataCount == 0;
}

template <class ValType>
bool TStack<ValType>::IsFull(void) const {
    return DataCount == MemSize;
}

template <class ValType>
void TStack<ValType>::Put(const ValType& val) {
    if (IsFull()) {
        throw "ERROR! Unable to put an element.";
    }
    Top = GetNextIndex(Top);
    pMem[Top] = val; //Видимо нужно перегрузить оператор присваивания, а значит и конструктор копирования!
    DataCount++;
}

template <class ValType>
TStack<ValType>& TStack<ValType>::operator=(const TStack& val) {
    if (this == &val) {
        return *this;
    }
    if (this != &val) {
        MemSize = val.MemSize;
        DataCount = val.DataCount;
        Top = val.Top;
        delete[] pMem;
        pMem = new ValType[MemSize];
        for (int i = 0; i < MemSize; i++) {
            pMem[i] = val.pMem[i];
        }
    }
    return *this;
}

template <class ValType>
ValType TStack<ValType>::Get(void) {
    if (IsEmpty()) {
        throw "ERROR! Unable to get an element.";
    }
    DataCount--;
    return pMem[Top--];
}

template <class ValType>
void TStack<ValType>::Print(void) {
    for (int i = 0; i < DataCount; i++) {
        cout << i + 1 << ") " << pMem[i] << endl;
    }
}
//Нужно ли перегружать операции ==, != ?
#endif
