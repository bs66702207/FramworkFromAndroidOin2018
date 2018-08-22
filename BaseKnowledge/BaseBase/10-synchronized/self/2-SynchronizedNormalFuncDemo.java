//修饰一个方法，这部分只是讲解，不需要编译
//Synchronized修饰一个方法很简单，就是在方法的前面加synchronized，
	public synchronized void method() {//todo};
//synchronized修饰方法和修饰一个代码块类似，只是作用范围不一样，修饰代码块是大括号括起来的范围，而修饰方法范围是整个函数。
//如将【Demo1】中的run方法改成如下的方式，实现的效果一样。
//Synchronized作用于整个方法的写法。

//写法一：
public synchronized void method()
{
	// todo
}

//写法二：
public void method()
{
	synchronized(this) {
	// todo
	}
}
/*
写法一修饰的是一个方法，写法二修饰的是一个代码块，但写法一与写法二是等价的，都是锁定了整个方法时的内容。

在用synchronized修饰方法时要注意以下几点：
1.synchronized关键字不能继承。
	虽然可以使用synchronized来定义方法，但synchronized并不属于方法定义的一部分，因此，synchronized关键字效果不能被继承。如果
在父类中的某个方法使用了synchronized关键字，而在子类中覆盖了这个方法，在子类中的这个方法默认情况下并不是同步的，而必须显式地
在子类的这个方法中加上synchronized关键字才可以。当然，还可以在子类方法中调用父类中相应的方法，这样虽然子类中的方法不是同步的，
但子类调用了父类的同步方法，因此，子类的方法也就相当于同步了。这两种方式的例子代码如下：
*/
//在子类方法中加上synchronized关键字
class Parent {
	public synchronized void method() {}
}
class Child extends Parent {
	public synchronized void method() {}
}
//在子类方法中调用父类的同步方法
class Parent {
	public synchronized void method() {}
}
class Child extends Parent {
	public void method() { super.method(); }
}

//2.在定义接口方法时不能使用synchronized关键字。
//3.构造方法不能使用synchronized关键字，但可以使用synchronized代码块来进行同步。
