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

    TStack(const TStack& s)
    {
        size = s.size;
        top = s.top;
        pMem = new T[s.size]
        copy(s.pMem, s.pMem + top + 1, pMem);
    }

    TStack& operator=(const TStack& s) {
        if (this != &s) {
            T* tmp = new T[s.size];
            size = s.size;
            top = s.top;
            delete[] pMem;
            pMem = tmp;
            for (size_t i = 0; i < size; i++)
            {
                pMem[i] = otherStack.pMem[i];
            }
        }
        return *this;
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
