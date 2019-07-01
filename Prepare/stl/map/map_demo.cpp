#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

//C++中map是根据红黑树来实现的

//访问操作
void visit_map() {
    map<int, int> T;
    T[0] = 11;
   	T[1] = 22;
    T[2] = 33;
    T[3] = 44;
    cout << "map容器中关键值为2的val为: ";
    cout << T.at(2) << endl;
    cout << "从头遍历该map元素" << endl;
    map<int, int>::iterator it = T.begin();

    while (it != T.end()) {
        cout << it->first << "  ->>>  " << it->second << endl;
        ++it;
    }

    cout << "find一个元素的迭代器并且访问它:";
    cout << T.find(3)->first << "  ->>>  " << T.find(3)->second << endl;
}

//插入的操作, 不是直接就把两个值传给他, 我们需要先把两个放进pair里面, 比如最基本的插入insert(pair<K,V>(key,val));
//这里每次插入的时候都要给pair传入模板类型有点繁琐, 所以我想着在这里封装一个函数让模板参数可以自动识别, 所以写一个函数为
template<typename K, typename V>
pair<K, V> mymake_pair(const K& key,const V& val) {
    return pair<K, V>(key, val);
}

void insert_map() {
    map<int, int> T;

    //***1*** 最正常的插入
    T.insert(pair<int, int>(1, 11));
    T.insert(pair<int, int>(2, 22));
    T.insert(pair<int, int>(3, 33));
    //这是最基本的插入操作，这里没有前插后插的，因为搜索树会负责给你安排位置
    //这里不需要你操心.

    T.insert(mymake_pair(4, 44));
    T.insert(mymake_pair(5, 55));
    T.insert(mymake_pair(6, 66));

    map<int, int>::iterator it1 = T.begin();

    cout << "遍历T中的元素:" << endl;
    while (it1 != T.end()) {
        cout << it1->first << " ";
        cout << "的val为" << " ";
        cout << it1->second << endl;
        ++it1;
    }
    cout << endl;

    //***2** 利用迭代器进行区间插入
    std::map<int, int> anothermap;
    anothermap.insert(T.begin(), T.find(6));
    map<int, int>::iterator it2 = anothermap.begin();

    cout << "遍历anothermap中的元素:" << endl;
    while (it2 != anothermap.end()) {
        cout << it2->first<< " ";
        cout << "的val为 " << " ";
        cout << it2->second<< endl;
        ++it2;
    }
}

void delete_map() {
    map<int, int> T;

    T.insert(mymake_pair(2, 22));
    T.insert(mymake_pair(3, 33));
    T.insert(mymake_pair(4, 44));
    T.insert(mymake_pair(5, 55));
    T.insert(mymake_pair(6, 66));
    T.insert(mymake_pair(1, 11));

    map<int, int>::iterator it1 = T.begin();

    cout << "遍历T中的元素:" << endl;
    while (it1 != T.end()) {
        cout << it1->first << " ";
        cout << "的val为" << " ";
        cout << it1->second << endl;
        ++it1;
    }
    cout << endl;

    //***2*** 删除单个迭代器
    map<int, int>::iterator it3 = T.find(2);
    //通过find拿到关键字为2的迭代器
    T.erase(it3);
    //然后删除该元素.
    it1 = T.begin();
    cout << "遍历T中的元素:" << endl;
    while (it1 != T.end())
    {
        cout << it1->first << " ";
        cout << "的val为" << " ";
        cout << it1->second << endl;
        ++it1;
    }
    cout << endl;

    //***2*** 删除迭代器区间
    it3 = T.find(3);
    //通过find拿到关键字为3的迭代器
    T.erase(it3, T.end());
    //删除掉it3到map容器结束的所有节点.
    it1 = T.begin();

    cout << "遍历T中的元素:" << endl;
    while (it1 != T.end())
    {
        cout << it1->first << " ";
        cout << "的val为" << " ";
        cout << it1->second << endl;
        ++it1;
    }
    cout << endl;

    //***3*** 终极大招 删除所有元素.
    T.insert(mymake_pair(1, 11));
    T.insert(mymake_pair(2, 22));
    T.insert(mymake_pair(3, 33));
    T.insert(mymake_pair(4, 44));
    T.insert(mymake_pair(5, 55));
    T.insert(mymake_pair(6, 66));
    T.clear();
    //删除所有元素.
    it1 = T.begin();
    cout << "遍历T中的元素:" << endl;
    while (it1 != T.end())
    {
        cout << it1->first << " ";
        cout << "的val为" << " ";
        cout << it1->second << endl;
        ++it1;
    }
    cout << endl;
}

int main(int argc, char* argv[]) {

    visit_map();
    cout << "--------------------" << endl;
    insert_map();
    cout << "--------------------" << endl;
    delete_map();

    return 0;
}
