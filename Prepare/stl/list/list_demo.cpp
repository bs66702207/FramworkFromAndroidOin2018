#include<stdio.h>
#include<iostream>
#include<list>
#include<string>
#include<algorithm>
using namespace std;

void PrintIt(string& StringToPoint) {
    cout << StringToPoint << endl;
}

class IsLoleina
{
public:
    bool operator()(string& name) {
        return name == "loleina";
    }
};

int main()
{
    list<string> test;
    list<string>::iterator testiterator;

    test.push_back("no");
    test.push_back("march");
    test.push_front("ok");
    test.push_front("loleina");
    test.push_front("begin");
    test.push_back("end");

    //注意: 不能用testiterator.begin()+2来指向list中的第三个对象，因为STL的list是以双链的list来实现的，所有的数据存放不一定是连续存放的。它不支持随机存取。
    for (testiterator = test.begin(); testiterator != test.end(); ++testiterator) {
        cout << *testiterator << endl;
    }
    cout << "-------------" << endl;

    for_each(test.begin(), test.end(), PrintIt);
    cout << "-------------" << endl;

    //STL的通用算法count()和count_it()用来给容器中的对象记数。就象for_each()一样，count()和count_if()算法也是在iterator范围内来做的。
    list<int> score;
    score.push_back(100);
    score.push_back(90);
    score.push_back(80);
    score.push_back(70);
    score.push_back(100);
    score.push_back(20);
    int countNum(0);
    countNum = count(score.begin(), score.end(), 100);
    cout << "there are " << countNum << " scores of 100" << endl;
    cout << "-------------" << endl;

    int countLoleina(0);
    countLoleina = count_if(test.begin(), test.end(), IsLoleina());
    cout << "there are " << countLoleina << " loleina" << endl;

    cout << "list test size() = " << test.size() << ", test empty() = "<< test.empty()<< endl;
    test.clear();
    cout << "list test size() = " << test.size() << ", test empty() = "<< test.empty()<< endl;

    char pause;
    cin>> pause;

    return 0;
}
