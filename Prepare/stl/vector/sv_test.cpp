#include "simple_vector.h"

int main()
{

    Vector<int> v;
    for(int i=0; i<10;i++)
        v.push_back(i);
    cout << "有效元素的个数: " << v.size() << endl;
    cout << "容量大小为: " << v.capacity() << endl;
    v.print();
    cout << "尾元素为: " << v.back() << endl;
    cout << "首元素为: " << v.front() << endl;
    cout<<endl<<endl;

    v.push_back(100);
    v.push_back(101);
    v.push_back(102);
    cout << "有效元素的个数: " << v.size() << endl;
    cout << "容量大小为: " << v.capacity() << endl;
    v.print();
    cout << "尾元素为: " << v.back() << endl;
    cout << "首元素为: " << v.front() << endl;
    cout<<endl<<endl;

    v.pop_back();
    v.pop_back();
    cout << "有效元素的个数: " << v.size() << endl;
    cout << "容量大小为: " << v.capacity() << endl;
    v.print();
    cout << "尾元素为: " << v.back() << endl;
    cout << "首元素为: " << v.front() << endl;
    cout<<endl<<endl;

    v.insert(1, 11);
    v.insert(2, 22);
    v.insert(3, 33);
    cout << "有效元素的个数: " << v.size() << endl;
    cout << "容量大小为: " << v.capacity() << endl;
    v.print();
    cout << "尾元素为: " << v.back() << endl;
    cout << "首元素为: " << v.front() << endl;
    cout<<endl<<endl;

    v.erase(4);
    cout << "有效元素的个数: " << v.size() << endl;
    cout << "容量大小为: " << v.capacity() << endl;
    v.print();
    cout << "尾元素为: " << v.back() << endl;
    cout << "首元素为: " << v.front() << endl;
    cout<<endl<<endl;

    v.resize(100, 888);
    cout << "有效元素的个数: " << v.size() << endl;
    cout << "容量大小为: " << v.capacity() << endl;
    v.print();
    cout << "尾元素为: " << v.back() << endl;
    cout << "首元素为: " << v.front() << endl;
    cout<<endl<<endl;

    v.clear();
    cout << "有效元素的个数: " << v.size() << endl;
    cout << "容量大小为: " << v.capacity() << endl;
    v.print();
    cout << "尾元素为: " << v.back() << endl;
    cout << "首元素为: " << v.front() << endl;
    cout<<endl<<endl;

    v.~Vector();
    cout << "有效元素的个数: " << v.size() << endl;
    cout << "容量大小为: " << v.capacity() << endl;
    cout<<endl<<endl;

    return 0;
}
