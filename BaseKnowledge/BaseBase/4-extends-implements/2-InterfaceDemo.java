/**
final译为最终，顾名思义：
(1)被final修饰的类，不可以被继承；
(2)被final修饰的方法，不可以被复写；
(3)被final修饰的变量，只能赋值一次,一般被用于修饰常量，规范写法是public static final PI。

接口interface
(1)interface用于定义接口，里面方法全是抽象方法，不可以被创建对象；其成员都有固定修饰符：
常量：public static final
方法：public abstract
记住：接口中的成员都是public的，不过有一点是如果你没有写固定修饰符，它会默认帮你加上。
(2)implements 使用该关键字来实现接口，class Test implements Inter，其中Inter是一个interface，子类对接口中的抽象方法全都覆盖后，子类才是一个实体类，否则是一个抽象类。
	System.out.println(t.NUM);
	System.out.println(Test.NUM);
	System.out.println(Inter.NUM);
(3)可以把接口看成是一个类，但注意只是看成，还是有区别的。接口可以被类多实现，而类是不可以被类多继承的。class Test implements Inter, InterA；这是一种多继承方式的转变--多实现，不同于c++支持多继承。
(4)接口之间可以继承interface B extends A;接口之间可以多继承，interface C extends A, B，不要接口A里写个void func()，B里写个int func()，这样是不会编译过去，程序也没有这么设计的，脑残。
(5)接口的意义，功能扩展，比如学生接口，张三是个学生，张三抽烟喝酒，那么抽烟喝酒就可以定义为接口去实现。
*/

interface Inter
{
	public static final int NUM = 3;
	public abstract void show();
}

interface InterA
{
	public abstract void method();
}

class Test implements Inter, InterA
{
	public void show()
	{
		
	}
	
	public void method()
	{
	
	}
}

interface A
{
	void methodA();
}

interface B extends A
{
	void methodB();
}

interface C extends A, B
{
	void methodC();
}

class D implements C
{
	public void methodA(){}
	public void methodB(){}
	public void methodC(){}
}

class InterfaceDemo
{
	public static void main(String[] args)
	{
		Test t = new Test();
		System.out.println(t.NUM);
		System.out.println(Test.NUM);
		System.out.println(Inter.NUM);
	}
}
