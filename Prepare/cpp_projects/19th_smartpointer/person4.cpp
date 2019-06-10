
#include <iostream>
#include <string.h>
#include <unistd.h>

using namespace std;

class Person {

public:

	Person() {
		cout <<"Pserson()"<<endl;
	}


	~Person()
	{
		cout << "~Person()"<<endl;
	}
	void printInfo(void)
	{
		cout<<"just a test function"<<endl;
	}
};

class sp {
private:
	Person *p;

public:
	sp() : p(0) {}
	
	sp(Person *other)
	{
		cout<<"sp(const Person *other)"<<endl;
		p = other;
	}

	sp(sp &other)
	{
		cout<<"sp(const Person *other)"<<endl;
		p = other.p;
	}

	~sp()
	{
		cout<<"~sp()"<<endl;
		if (p)
			delete p;
	}

	Person *operator->()
	{
		return p;
	}
	
};

void test_func(sp &other)
{
	sp s = other;

	s->printInfo();

	//Person *p = new Person();
	//p->printInfo();
	//delete p;

	
}

/**
person4.cpp: In function ��int main(int, char**)��:
person4.cpp:88:24: error: invalid initialization of non-const reference of type ��sp&�� from an rvalue of type ��sp��
  sp other = new Person();
                        ^
person4.cpp:40:2: note:   initializing argument 1 of ��sp::sp(sp&)�� //û�а취��spת����sp����
  sp(sp &other)
  ^
person4.cpp:34:2: note:   after user-defined conversion: sp::sp(Person*) //û�а취��spת����Personָ��
  sp(Person *other)
*/

int main(int argc, char **argv)
{	
	int i;

	/* �൱��:
	 * 1. Person *p = new Person();
	 * 2. sp tmp(p);  ==> sp(Person *other)
	 * 3.
	 * 3.1 sp other(tmp);  ==> sp(sp &other2)
	       ��������: sp &other2 = tmp; // �����﷨
	                 const sp& other2 = tmp; //ok
	 * ��
	 * 3.2 sp other(tmp ==> Person*);  ==>sp(Person *other)
	 */
	
	sp other = new Person();

	for (i = 0; i < 2; i++)
		test_func(other);
	return 0;
}

