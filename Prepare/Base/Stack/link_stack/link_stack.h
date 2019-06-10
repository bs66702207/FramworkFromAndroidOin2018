
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

#define DEBUG_1 0
#define DEBUG_2 0

template <typename T>
class node {
public:
    T *value;
    class node<T>* next;
};

template <typename T>
class link_stack {
public:
    link_stack();
    ~link_stack();
    void push(T t);
    T peek();
    T pop();
    int size();
    int isEmpty();
    void traversal();

private:
    node<T>* sp;
    node<T>* head;
    int count;
};

template <typename T>
link_stack<T>::link_stack() {
    head = new node<T>();
    head->next = NULL;
    sp = head;
    count = 0;
}

template <typename T>
link_stack<T>::~link_stack() {
    node<T>* tmp = NULL;
    while(head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

template <typename T>
void link_stack<T>::push(T t) {
    node<T> *n = new node<T>();
    n->value = new T();
    memcpy(n->value, &t, sizeof(T));
    sp->next = n;
    sp = n;
    count++;
    if(DEBUG_1) cout << *(n->value) << endl;
}

template <typename T>
T link_stack<T>::peek() {
    return *(sp->value);
}

template <typename T> 
void link_stack<T>::traversal() {
    class node<T>* tmp = head;
    tmp = tmp->next;
    for(int i = 0; i < count; i++) {
        cout << tmp->value  << endl;
        tmp = tmp->next;
    }
}

template <typename T>
T link_stack<T>::pop() {
    T ret = *(sp->value);
    if(DEBUG_2) {
        cout << "pop() count: " << count << "&sp" << sp << endl;
    }
    class node<T>* tmp = head;//第0个是head，不保存元素，所以元素从1开始计算
    for(int i = 1; i < count; i++) {
        tmp = tmp->next;
        if(DEBUG_2) cout << "count: " << count << endl;
    }
    if(DEBUG_2) cout << "--------------------tmp->value = " << *(tmp->next->value) << endl;
    free(tmp->next);
    sp = tmp;
    count--;
    return ret;
}

template <typename T>
int link_stack<T>::size() {
    return count;
}

template <typename T>
int link_stack<T>::isEmpty() {
    return size()==0;
}
