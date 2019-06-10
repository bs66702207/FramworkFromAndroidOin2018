#include "complex_vector.h"

int main()
{

    Vector<int> v;
    for(int i=0; i<10;i++)
        v.push_back(i);

    Vector<int>::Iterator it = v.Begin();
    while (it != v.End()) {
        cout << *it << "  ";
        ++it; //使用前置++,是因为这样不会创建临时对象，比后置++的效率高
    }
    cout << endl;

    return 0;
}
