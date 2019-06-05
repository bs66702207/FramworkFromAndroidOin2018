#include "static_stack.h"

int main()
{
    //Stack<int> *test_sk = new Stack<int>();
    Stack<char> *test_sk = new Stack<char>();

    test_sk->push('h');
    test_sk->push('e');
    test_sk->push('l');
    test_sk->push('l');
    test_sk->push('o');
    cout << "test_sk->size(): " << test_sk->size()  << endl;
    cout << "the top element is " << test_sk->peek() << endl;
    //test_sk->traversal();
    cout << "-----------------------------------------------------" << test_sk->peek() << endl;
    cout << "now pop all elemants" << endl;
    while(test_sk->size() != 0) {
        cout << test_sk->pop() << " " << endl;
    }
   
#if 1
    test_sk->push('w');
    test_sk->push('o');
    test_sk->push('r');
    test_sk->push('l');
    test_sk->push('d');
    cout << test_sk->size() << endl;
    cout << "the top element is " << test_sk->peek() << endl;

    test_sk->push('1');
    test_sk->push('2');
    test_sk->push('3');
    test_sk->push('4');
    test_sk->push('5');
    test_sk->push('6');
    test_sk->push('7');
    test_sk->push('8');
    test_sk->push('9');
    test_sk->push('x');
    cout << "now pop all elemants" << endl;
    while(test_sk->size() != 0) {
        cout << test_sk->pop() << " " << endl;
    }
#endif
    delete test_sk;

    return 0;
}
