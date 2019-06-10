#include<iostream>
using namespace std;
#include<assert.h>

template <class T>
//迭代器版本, vectro的迭代器其实就是原生态的指针
class Vector
{
public:
    typedef T* Iterator;
public:
    Vector();
    Vector(T* array, size_t size);
    Vector(const Vector<T>& v);//拷贝构造函数
    Vector<T>& operator=(const Vector<T>& v);
    ~Vector();
    void push_back(const T &data);//尾插
    void pop_back();//尾删
    void insert(size_t pos, const T &t);//任意位置的插入
    void erase(size_t pos);//任意位置的删除
    size_t size();
    size_t capacity() const;
    bool is_empty();
    void clear();//删除顺序表中所有元素
    //将有效元素的个数改变为new_size个
    //第二个参数含义：空间变大后，变大的空间中需要存储的数据，一般情况下，该参数是有缺省值的
    void resize(size_t new_size, const T &data);
    const T& back();//返回尾元素
    const T& front() const;//返回首元素
    void print();//打印元素
    const T& operator[](size_t index) const;//重载[]

    //以下是Vector的迭代器的接口
    Iterator Begin()
    {
        return _start;
    }
    Iterator End()
    {
        return _finish;
    }

private:
    void _CheckCapacity();//检测容量的函数，容量不够时增容
    void _print();//打印的实现

    template <class U>//注意友元函数是函数不是类内函数所以也要加template
    friend ostream& operator<<(ostream &_cout, const Vector<U> &d);//重载输出运算符

    T* _start;//指向空间的起始位置
    T* _finish;//指向空间最后一个元素的后面
    T* _endOfStorage;//标记空间的容量，指向空间末尾
};

template <class T>
Vector<T>::Vector() : _start(NULL), _finish(NULL), _endOfStorage(NULL) {}

template <class T>
Vector<T>::Vector(T* array, size_t size) : _start(new T[size]) {
    for(int i=0; i<size; i++) {
        _start[i] = array[i];
    }
    _finish = _start + size;
    _endOfStorage = _start + size;
}

template <class T>
Vector<T>::Vector(const Vector<T> &v) {
    int size = v.size();
    _start = new T[size];
    for(int i=0; i<size; i++) {
         _start[i] = v[i]; 
    }
    _finish = _start + size;
    _endOfStorage = _start + size;
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v) {
    int size = v.size();
    assert(this != &v);
    //if(this != &v) {
        _start = new T[size];
        for(int i=0; i<size; i++) {
            _start[i] = v._start[i];
        }
        _finish = v._finish;
        _endOfStorage = v._endOfStorage;
    //}
    return *this;
}

template <class T>
Vector<T>::~Vector() {
    if(_start) {
         delete _start;
         _start = _finish = _endOfStorage = NULL;
    }
}


template <class T>
void Vector<T>::push_back(const T &data) {
    _CheckCapacity();//在插入数据之前，需要先检测以下容量，因为空间如果不足的话，是不能存储数据的
    (*_finish) = data;
    _finish++;
}


template <class T>
void Vector<T>::pop_back() {
    --_finish;
}

template <class T>
void Vector<T>::insert(size_t pos, const T &data) {
    assert(pos < size());
    _CheckCapacity();
    for(size_t i=size(); i>=pos; i--) {
        _start[i] = _start[i-1];
    }
    _start[pos] = data;
    ++_finish;
}

template <class T>
void Vector<T>::erase(size_t pos) {
    assert(pos < size());
    for(size_t i=pos+1; i<size(); i++) {
         _start[i-1] = _start[i];
    }
    --_finish;
}

template <class T>
size_t Vector<T>::size() {
    return _finish - _start;
}

template <class T>
bool Vector<T>::is_empty() {
    return _start == _finish;
}

template <class T>
const T& Vector<T>::operator[](size_t index) const {
    assert(index < size());
    return _start[index];
}

template <class T>
size_t Vector<T>::capacity() const {
    return _endOfStorage - _start;
}

template <class T>
void Vector<T>::clear() {
    for(int i=0; i<size(); i++)
        _start[i] = 0;
    _finish = _start;
}

template <class T>
void Vector<T>::resize(size_t new_size, const T &data) {
    if(new_size < size()) {//new_size小于旧空间中有效元素的个数
        _finish = _start + new_size;
    } else if(new_size > size() && new_size < capacity()) {
        for(size_t i=size(); i<new_size; i++) {
            _start[i] = data;
        }
        _finish = _start + new_size;
    } else {
        T *tmp = new T[new_size];
        for(size_t i=0; i<size(); i++) {
            tmp[i] = _start[i];
        }
        for(size_t i=size(); i<new_size; i++) {
            tmp[i] = data;
        }
        delete _start;
        _start = tmp;
        _finish = _start + new_size;
        _endOfStorage = _start + new_size;
    }
}

template <class T>
const T& Vector<T>::back() {
    assert(_start);
    return _start[size()-1];
}

template <class T>
const T& Vector<T>::front() const {
    assert(_start);
    return _start[0];
}

template <class T>
void Vector<T>::print() {
    _print();
}

template <class T>
void Vector<T>::_CheckCapacity() {
    if(_finish == _endOfStorage) {//此时表示空间已满
        size_t old_size = size();
        size_t new_size = old_size * 2 + 3;
        T *tmp = new T[new_size];
        if(_start) {
            for (size_t  i=0; i<old_size; ++i)
                tmp[i] = _start[i];
            delete _start;
        }
        _start = tmp;
        _finish = _start + old_size;
        _endOfStorage = _start + new_size;
    }
}

template <class T>
void Vector<T>::_print() {
    for (size_t i=0; i<size(); ++i)
        cout << _start[i] << " ";
    cout << endl;
}

//重载输出运算符
template <class U>
ostream& operator<<(ostream &_cout, const Vector<U> &d) {
    for (size_t i = 0; i < d.size(); ++i)
        _cout << d[i] << " ";
    return _cout;
}
