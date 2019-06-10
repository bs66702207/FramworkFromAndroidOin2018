/*
 栈通常包括的三种操作：push、peek、pop。
 push -- 向栈中添加元素。
 peek -- 返回栈顶元素。
 pop  -- 返回并删除栈顶元素的操作。
*/

#ifndef STATIC_STACK_DEMO
#define STATIC_STACK_DEMO
#include <iostream>
using namespace std;

template <typename T>
class Stack { 
public:
    Stack();
    ~Stack();
    void push(T t);
    T peek();
    T pop();
    int size();
    int isEmpty();

private:
    T* sk;
    int count;
};

template <typename T>
Stack<T>::Stack() {
    count = 0;
    sk = new T[12];
    if(sk == NULL) {
        cout << "arr malloc error!"  << endl;
    }
}

template <typename T>
Stack<T>::~Stack() {
    if(sk != NULL) {
        delete[] sk;
        sk = NULL;
    }
}

template <typename T>
void Stack<T>::push(T t) {
    sk[count] = t;
    count++;
}

template <typename T>
T Stack<T>::peek() {
    return sk[count-1];
}

template <typename T>
T Stack<T>::pop() {
    T ret = sk[count-1];
    count--;
    return ret;
}

template <typename T>
int Stack<T>::size() {
    return count;
}

template <typename T>
int Stack<T>:: isEmpty() {
    return size()==0;
}

#endif
