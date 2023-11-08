#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack 
{
    T* pMem;
    size_t size;
    int top;
public:
    TStack() 
    {
        size = 1;
        top = -1;
        pMem = new T[size];
    }

    ~TStack() { 
        delete[] pMem; 
    }

    T Pop() {
        if (top < 0) {
            throw "Stack is empty"; 
        }
        return pMem[top--];
    }

    void Push(T val) {
        if (top + 1 == MaxStackSize)
            throw "Maximum number of items reached";
        if (top == size - 1)
        {
            size *= 2;
            T* tmp = new T[size];
            std::copy(pMem, pMem + top + 1, tmp);
            delete[] pMem;
            pMem = tmp;
        }
        pMem[++top] = val;
    }

    size_t GetSize(){ 
        return top + 1; 
    }

    bool IsEmpty(){
        return top == -1; 
    }
};
#endif
