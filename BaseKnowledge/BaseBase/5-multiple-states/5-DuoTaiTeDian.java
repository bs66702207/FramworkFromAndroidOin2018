/**
例子：两个类Fu和Zi，Zi继承Fu，然后main中Fu test = new Zi(); 利用test执行了func1、func2等等
在编译时期：参阅Fu(引用型变量所属的类)中是否有func1、func2等等，如果有，编译通过；否则失败。
在运行时期：参阅Zi(对象所属的类)中是否有func1、func2等等，先以Zi为准，Zi如果没有func1，再去调用Fu的func1。

简单总结：非static成员函数多态调用时，编译看左边，运行看右边。但是，成员变量调用时，都参考左边；
前面既然说了是非static成员函数，那么static呢，呵呵，参考的是左边，这跟static的特点有关系，
因为static不需要对象引用，类.静态方法、对象.静态方法都是调用的静态方法区对应的静态方法(这也是为啥静态方法不能访问非静态成员变量的原因)。
再但是，“但是”后面这些东西面试可能会问到，但是开发时，不要这么写，太混乱，阅读性太差。
*/

class Fu
{
	int num = 5;
	void method1()
	{
		System.out.println("fu method 1");
	}
	void method2()
	{
		System.out.println("fu method 2");
	}
	static void method4()
	{
		System.out.println("fu method 4");
	}
}

class Zi extends Fu
{
	int num = 8;
	void method1()
	{
		System.out.println("zi method_1");
	}
	void method3()
	{
		System.out.println("zi method_3");
	}
	static void method4()
	{
		System.out.println("zi method_4");
	}
}

class DuoTaiTeDian
{
	public static void main(String[] args)
	{
		Fu f = new Zi();
		f.method1();
		f.method4();
	}
}
