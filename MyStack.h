#ifndef DATASTRUCTUREPROJECT1_MYSTACK_H
#define DATASTRUCTUREPROJECT1_MYSTACK_H

#include <iostream>
using namespace std;

template<class item>
class MyStack {
public:
    MyStack(int size) {
        this->top = -1;
        this->size = size;
        this->stack = (item *) malloc(size);
    }

    ~MyStack(){
        delete(this->stack);
    }

    void push(item data) {
        if (this->isFull())
            cout << "Your stack is full!";
        else {
            this->top++;
            this->stack[this->top] = data;
        }
    }

    item pop() {
        if (this->isEmpty())
            cout << "Your stack is empty!";
        else {
            item data = this->stack[this->top];
            this->top--;
            return data;
        }
    }

    bool isEmpty() {
        if (this->top == -1)
            return true;
        return false;
    }

    bool isFull() {
        if (this->top == this->size - 1)
            return true;
        return false;
    }

    item topValue() {
        return this->stack[this->top];
    }

private:
    item *stack;
    int top;
    int size;
};

#endif
