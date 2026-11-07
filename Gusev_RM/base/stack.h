#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <utility>
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
    TStack(int _size)
    {
        size = _size;
        top = -1;
        if ((size < 1) || (size > MaxStackSize))
            throw std::out_of_range("Wrong size");
        pMem = new T[size];
    }
    ~TStack()
    {
        delete[] pMem;
    }

    void push(const T& value) {
        if (top >= size - 1) {
            throw std::length_error("limit");
        }
        top += 1;
        pMem[top] = value;
    }
    T pop() {
        if (top == -1) {
            throw std::out_of_range("Stack is empty");
        }
        return pMem[top--];
    }
    T peek() const {
        if (top == -1) {
            throw std::out_of_range("Stack is empty");
        }
        return pMem[top];
    }
    bool is_empty() const {
        return(top == -1);
    }
    TStack(const TStack& other) {
        size = other.size;
        top = other.top;
        pMem = new T[other.size];
        std::copy(other.pMem, other.pMem + size, pMem);
    }
    friend void swap(TStack& lhs, TStack& rhs) noexcept {
        std::swap(lhs.pMem, rhs.pMem);
        std::swap(lhs.size, rhs.size);
        std::swap(lhs.top, rhs.top);
    }
    TStack& operator=(const TStack& a) {
        if (this != &a) {
            TStack temp(a);
            swap(*this, temp);
        }
        return *this;
    }
    TStack (TStack&& other) noexcept: pMem(nullptr), size(0), top(-1){
        swap(*this, other);
    }
    TStack& operator=(TStack&& a) noexcept{
        if (this != &a) {
            swap(*this, a);
        }
        return *this;
    }
};
#endif