/**
throws 使用在函数上；throw使用在函数内。
throws后面跟的异常类，可以跟多个，用逗号隔开；throw后跟的是异常对象。

java.lang.RuntimeException
这个类及其子类可以在函数内throw而不用在函数上throws声明；如果在函数上throws声明了，在调用时也不需要try和catch或者throw。
该类和他的小弟如果发生异常，就会终止程序。
该类是个常用的被继承的异常类，比较省事。

对于异常分两种：
(1)编译时检测异常，即非Runtime异常，该方法如果throw，则必须throws，而且调用者调用时必须做处理，要么try、catch要么也抛出。
(2)编译时不被检测异常，即Runtime异常，该方法可以throw，而不必throws，即使是throws了，调用者也不必管，直接调用该方法即可。

*/

class Demo 
{
	int div1(int a, int b) //throws ArithmeticException
	{
		if(b==0)
			throw new ArithmeticException("000");
		return a/b;
	}

	int div2(int a, int b) throws ArithmeticException
	{
		return a/b;
	}
}
class ExceptionThrowsAndThrow
{
	public static void main(String[] args)
	{
		Demo d= new Demo();
			//int x = d.div1(4, 0);
			//System.out.println("x="+x);

			int x = d.div2(4, 0);
			System.out.println("x="+x);
		System.out.println("over");
	}
}
