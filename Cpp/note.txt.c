Cpp/cpp_projects/19th_smartpointer/person3.cpp //sp为栈变量，里面维护堆上的person
Cpp/cpp_projects/19th_smartpointer/person5.cpp //重复析构sp，导致sp维护的对象delete两次，所以需要加入引用计数
Cpp/cpp_projects/19th_smartpointer/person6.cpp //加入引用计数机制
Cpp/cpp_projects/19th_smartpointer/person7.cpp //加入(*sp).XXX操作
Cpp/cpp_projects/19th_smartpointer/person8.cpp //将计数机制抽离出来class RefBase，让Person来继承
Cpp/cpp_projects/19th_smartpointer/person9.cpp //变成类模板，不仅仅可以指向Person

