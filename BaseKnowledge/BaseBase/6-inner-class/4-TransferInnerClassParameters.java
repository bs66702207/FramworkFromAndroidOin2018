/**
new 匿名类并且实现父类/接口方法然后当参数传递给func

func(new A()
{
	public void method()
	{
	}
});
*/

interface Inter
{
	public abstract void method();
}

class Test
{
	public static Inter function()
	{
		return (new Inter()
		{
			public void method()
			{
				System.out.println("test1!");
			}
		});
	}
	
}

class TransferInnerClassParameters
{
	public static void main(String[] args)
	{
		Test.function().method();//类名.func1().func2()，说明func1()返回的是一个对象，所以可以func1().func2()调用
	
		show(new Inter() 
		{
			public void method()
			{
					System.out.println("test2!");
			}
		});

	}
	public static void show(Inter in)
	{
		in.method();
	}
}

class InterTest
{

	public static void main(String[] args)
	{
		new Object()
		{
			public void function()
			{
				System.out.println("hoho");
			}
		}.function();
	}
}
