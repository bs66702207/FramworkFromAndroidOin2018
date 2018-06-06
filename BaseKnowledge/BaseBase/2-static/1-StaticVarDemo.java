/**
说明
(1)如果一个class Person中有一个表示国籍的成员变量String country ="CN"; 如果你总是new对象，那么这个country太多，而且占用很多堆内存，
   这时候你可以用static来修饰country，这样这个country就不在堆内存当中，而是存在方法区(也叫共享区、数据区，书翻译不一样，这里面存储的
   是方法和共享数据)，所有的Person对象可以共享country。
(2)可以用Person.country调用country；也就是说多了一种调用方式，类名调用。
(3)static 成员变量优先于类存在，比如new Person之前，country已经存在，但是name是不存在的。类一进内存，country即存在；
   对象一创建，name就会产生；对象消失了，name也就消失了，但是country存在；类一消失，country就会消失了。
(4)static方法public static void show()，也可以用Person.show()调用。
(5)static方法只能访问静态方法和静态成员，所以就不能用this，因为静态优先于对象存在。而非静态方法既可以访问静态的也可以访问非静态。
(6)静态方法中不可以用super关键字。
(7)main要求是static
(8)static是修饰成员的，不能修饰局部。

评价
利处：节省空间，直接可以用类名调用。
弊端：生命周期过长，访问出现局限性，只能访问static。

啥时候使用
(1) 共享数据 比如同一个学校，使用static
(2) 当功能内部没有访问到非静态数据
(3) 专有工具类，比如class ArrayTool，严禁的话，需要把构造方法私有化，这样不能创建对象了
*/

class Person
{
	static String name;
	static String country = "CN";
	public static void show()
	{
		System.out.println(name+"::"+country);
	}
}

class PersonDemo
{
	public static void main(String[] args)
	{
		Person p = new Person();
		p.name = "zhangsan";
		p.show();
		p.country = "USA";
		p.show();
	}
}
