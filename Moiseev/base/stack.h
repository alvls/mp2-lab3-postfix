#ifndef __STACK_H__
#define __STACK_H__

using namespace std;


template <class T>
class TStack {

    int top;
    size_t memSize;
    T* pMem;

public:
    TStack() : top(-1), memSize(1), pMem(new T[memSize]) {}

    ~TStack() { delete[] pMem; }

    size_t getSize() const { return top + 1; }

    bool IsEmpty() const { return top == -1; }

    T Pop() {

        if (top < 0) { throw exception("Stack is empty"); }

        return pMem[top--];
    }

    void Push(const T& val) {

        if (top == memSize - 1)
        {
            T* tmpMem = new T[memSize * 2];
            copy(pMem, pMem + memSize, tmpMem);
            delete[] pMem;
            pMem = tmpMem;
            memSize *= 2;
        }

        pMem[++top] = val;
    }
};

#endif
