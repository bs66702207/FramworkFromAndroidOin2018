#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//升序比较函数
int compare1(const int &a, const int &b) {
    return a < b;
}

//降序比较函数
int compare2(const int &a, const int &b) {
    return a > b;
}

void vector_demo() {

    vector<int> v;
    vector<int>::iterator it;
    for(int i=1000000; i>=1; i--) {
        v.push_back(i);
    }

//1 c
    cout<<"元素的个数: "<< v.size() <<endl;
    cout<<"迭代输出: ";
    cout<<"实际所占内存的大小: "<< v.capacity() <<endl;
    for(it=v.begin(); it!=v.end(); it++)
        cout << *it << " ";
    cout<<endl;
    it -= 1;
    cout<<"迭代结束之后, it减去多增加的1, 得到最后一个元素的值: "<<*it<<endl;
    cout<<endl<<endl;

//2 d
    v.erase(it);
    cout<<"删除最后一个元素, 元素的个数: "<< v.size() <<endl;
    cout<<"实际所占内存的大小: "<< v.capacity() <<endl;
    sort(v.begin(), v.end());
    cout<<"默认排序后, 迭代输出: ";
    for(it=v.begin(); it!=v.end(); it++)
        cout << *it << " ";
    cout<<endl;
    sort(v.begin(), v.end(), compare1);
    sort(v.begin(), v.end(), less<int>());//与上一行实现同一个功能
    cout<<"升序排序后, 迭代输出: ";
    for(it=v.begin(); it!=v.end(); it++)
        cout << *it << " ";
    cout<<endl;
    sort(v.begin(), v.end(), compare2);
    sort(v.begin(), v.end(), greater<int>());//与上一行实现同一个功能
    cout<<"降序排序后, 迭代输出: ";
    for(it=v.begin(); it!=v.end(); it++)
        cout << *it << " ";
    cout<<endl;
    cout<<endl<<endl;

//3 u
    v.insert(v.begin(), 100);
    cout<<"在首部插入一个elem, 第一个元素为: "<< v.front() <<endl;
    cout<<"元素的个数: "<< v.size() <<endl;
    cout<<"实际所占内存的大小: "<< v.capacity() <<endl;
    cout<<"插入后，迭代输出: ";
    for(it=v.begin(); it!=v.end(); it++)
        cout << *it << " ";
    cout<<endl;
    cout<<endl<<endl;

    v.push_back(101);
    cout<<"在尾部插入一个elem, 最后一个元素为: "<< v.back() <<endl;
    cout<<"元素的个数: "<< v.size() <<endl;
    cout<<"插入后，迭代输出: ";
    for(it=v.begin(); it!=v.end(); it++)
        cout << *it << " ";
    cout<<endl;
    cout<<endl<<endl;

//4 r
    cout<<"下标访问元素: "<<endl;
    cout<<"v[0] = "<<v[0]<<endl;
    cout<<"v[20] = "<<v[20]<<endl;//不检查是否越界

    cout<<"at方法访问元素: "<<endl;
    cout<<"v[0] = "<<v.at(0)<<endl;
    try {
        cout<<"v[20] = "<<v.at(20)<<endl;//检查是否越界, 如果越界会抛出异常
    } catch (exception e) {
         cout << e.what() << endl;
    }
    cout<<endl;
    cout<<endl<<endl;

//5 s
    it = find(v.begin(), v.end(), 101);
    if(it != v.end()) {
        cout << "found " << *it << endl;
    } else {
        cout << "not found" << endl;
    }

//6 d
    it = remove(v.begin(), v.end(), 2) ;
    cout<<"\"remove\"2之后，元素的个数: "<< v.size() <<endl;
    cout<<"\"remove\"2之后，实际所占内存的大小: "<< v.capacity() <<endl;
    cout<<"\"remove\"2之后，迭代输出: ";
    for(it=v.begin(); it!=v.end(); it++)
        cout << *it << " ";
    cout<<endl;

    for(it=v.begin(); it!=v.end(); it++) {
        if(*it == 101) {
            //cout << &*it << endl;
            it = v.erase(it);//it会++一次
            //cout << &*it << endl;
            it--;//删除完后需要--，否则最终循环越界
        }
    }
    cout<<"删除101之后，元素的个数: "<< v.size() <<endl;
    cout<<"删除101之后，实际所占内存的大小: "<< v.capacity() <<endl;
    cout<<"删除101之后，迭代输出: ";
    for(it=v.begin(); it!=v.end(); it++)
        cout << *it << " ";
    cout<<endl;

    v.pop_back();
    cout<<"pop_back一个尾部元素之后，元素的个数: "<< v.size() <<endl;
    cout<<"pop_back一个尾部元素之后, 实际所占内存的大小: "<< v.capacity() <<endl;
    cout<<"pop_back一个尾部元素之后, 迭代输出: ";
    for(it=v.begin(); it!=v.end(); it++)
        cout << *it << " ";
    cout<<endl;
    cout<<endl;

//7 free mem
    vector<int> vv;
    for(int i=10; i>=1; i--) {
        vv.push_back(i+1000);
    }
    v.swap(vv);
    cout<<"v.swap(vv)之后，元素的个数: "<< v.size() <<endl;
    cout<<"v.swap(vv)之后, 实际所占内存的大小: "<< v.capacity() <<endl;
    for(it=v.begin(); it!=v.end(); it++)
        cout << *it << " ";
    cout<<endl;

    v.clear();
    cout<<"clear()之后，元素的个数: "<< v.size() <<endl;
    cout<<"clear()之后, 实际所占内存的大小: "<< v.capacity() <<endl;

    cout<<"().swap(v)之前，pause" << endl;
    char s_pause;
    cin>> s_pause;
    vector<int> ().swap(v);
    cout<<"().swap(v)之后，元素的个数: "<< v.size() <<endl;
    cout<<"().swap(v)之后, 实际所占内存的大小: "<< v.capacity() <<endl;
}

int main(int argc, char* argv[]) {
    vector_demo();
    cout<<"pause"<<endl;
    char pause;
    cin>> pause;
}
