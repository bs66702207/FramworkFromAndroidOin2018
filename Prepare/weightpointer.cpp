#include <stdio.h>
#include <utils/RefBase.h>
 
#define INITIAL_STRONG_VALUE (1<<28)
 
using namespace android;
 
class WeightClass : public RefBase
{
public:
        void printRefCount()
        {
                int32_t strong = getStrongCount();
                weakref_type* ref = getWeakRefs();
 
                printf("-----------------------\n");
                printf("Strong Ref Count: %d.\n", (strong  == INITIAL_STRONG_VALUE ? 0 : strong));
                printf("Weak Ref Count: %d.\n", ref->getWeakCount());
                printf("-----------------------\n");
        }
};
 
class StrongClass : public WeightClass
{
public:
        StrongClass()
        {
                printf("Construct StrongClass Object.\n");
        }
 
        virtual ~StrongClass()
        {
                printf("Destory StrongClass Object.\n");
        }
};
 
 
class WeakClass : public WeightClass
{
public:
        WeakClass()
        {
                extendObjectLifetime(OBJECT_LIFETIME_WEAK);
 
                printf("Construct WeakClass Object.\n");
        }
 
        virtual ~WeakClass()
        {
                printf("Destory WeakClass Object.\n");
        }
};
 
class ForeverClass : public WeightClass
{
public:
        ForeverClass()
        {
                extendObjectLifetime(OBJECT_LIFETIME_FOREVER);
 
                printf("Construct ForeverClass Object.\n");
        }
 
        virtual ~ForeverClass()
        {
                printf("Destory ForeverClass Object.\n");
        }
};
 
 
void TestStrongClass(StrongClass* pStrongClass)
{
//首先定义一个弱批针wpOut指向从main函数传进来的StrongClass对象，这时候我们可以看到StrongClass对象的强引用计数和弱引用计数值分别为0和1
        wp<StrongClass> wpOut = pStrongClass;
        pStrongClass->printRefCount();
 //接着在一个大括号里面定义一个强指针spInner指向这个StrongClass对象，这时候我们可以看到StrongClass对象的强引用计数和弱引用计数值分别为1和2
        {
                sp<StrongClass> spInner = pStrongClass;
                pStrongClass->printRefCount();
        }
//当程序跳出了大括号之后，强指针spInner就被析构了，从上面的分析我们知道，强指针spInner析构时，会减少目标对象的强引用计数值，因为前面得到的强引用计数值为1，这里减1后，就变为0了，又由于这个StrongClass对象的生命周期只受强引用计数控制，因此，这个StrongClass对象就被delete了，这一点可以从后面的输出（“Destory StrongClass Object.”）以及试图把弱指针wpOut提升为强指针时得到的对象指针为0x0得到验证。
        sp<StrongClass> spOut = wpOut.promote();
        printf("spOut: %p.\n", spOut.get());
}
 
void TestWeakClass(WeakClass* pWeakClass)
{
        wp<WeakClass> wpOut = pWeakClass;
        pWeakClass->printRefCount();
 
        {
                sp<WeakClass> spInner = pWeakClass;
                pWeakClass->printRefCount();
        }
//  TestWeakClass函数和TestStrongClass函数的执行过程基本一样，所不同的是当程序跳出大括号之后，虽然这个WeakClass对象的强引用计数值已经为0，但是由于它的生命周期同时受强引用计数和弱引用计数控制，而这时它的弱引用计数值大于0，因此，这个WeakClass对象不会被delete掉，这一点可以从后面试图把弱批针wpOut提升为强指针时得到的对象指针不为0得到验证。
        pWeakClass->printRefCount();
        sp<WeakClass> spOut = wpOut.promote();
        printf("spOut: %p.\n", spOut.get());
}
 
 
void TestForeverClass(ForeverClass* pForeverClass)
{
        wp<ForeverClass> wpOut = pForeverClass;
        pForeverClass->printRefCount();
 
        {
                sp<ForeverClass> spInner = pForeverClass;
                pForeverClass->printRefCount();
        }
}
 
int main(int argc, char** argv)
{
        printf("Test Strong Class: \n");
        StrongClass* pStrongClass = new StrongClass();
        TestStrongClass(pStrongClass);
/*
Test Strong Class: 
Construct StrongClass Object. 
----------------------- 
Strong Ref Count: 0. 
Weak Ref Count: 1. 
----------------------- 
----------------------- 
Strong Ref Count: 1. 
Weak Ref Count: 2. 
----------------------- 
Destory StrongClass Object. 
spOut: 0x0.
---------------------  
*/

        printf("\nTest Weak Class: \n");
        WeakClass* pWeakClass = new WeakClass();
        TestWeakClass(pWeakClass);
/*
Test Weak Class: 
Construct WeakClass Object. 
----------------------- 
Strong Ref Count: 0. 
Weak Ref Count: 1. 
----------------------- 
----------------------- 
Strong Ref Count: 1. 
Weak Ref Count: 2. 
----------------------- 
----------------------- 
Strong Ref Count: 0. 
Weak Ref Count: 1. 
----------------------- 
spOut: 0xa528. 
Destory WeakClass Object.
--------------------- 
*/

        printf("\nTest Froever Class: \n");
        ForeverClass* pForeverClass = new ForeverClass();
        TestForeverClass(pForeverClass);
/* 
Test Froever Class: 
Construct ForeverClass Object. 
----------------------- 
Strong Ref Count: 0. 
Weak Ref Count: 1. 
----------------------- 
----------------------- 
Strong Ref Count: 1. 
Weak Ref Count: 2. 
-----------------------
--------------------- 
*/


        pForeverClass->printRefCount();
        delete pForeverClass;
/*
-----------------------
Strong Ref Count: 0.
Weak Ref Count: 0.
-----------------------
Destory ForeverClass Object.
*/
        return 0;
}
