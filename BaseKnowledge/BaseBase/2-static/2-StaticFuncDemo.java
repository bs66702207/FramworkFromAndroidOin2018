//静态代码块/构造代码块，特点：随着类的加载而运行，只执行一次，并且优先于主函数执行，构造代码块没有static

class StaticFunc
{
	int a = 8;
	{
		System.out.println("ClassCreateCodePart 1! a=" + a);
	}
	static
	{
		System.out.println("ClassStatocCodePart!");
	}
	
	{
		System.out.println("ClassCreateCodePart 2!");
	}
	
	StaticFunc(int x)
	{
		System.out.println(x);
	}

	int b = 18;
	{
		System.out.println("ClassCreateCodePart 3! b=" + b);
	}
}

class StaticFuncDemo
{
	public static void main(String[] args)
	{
		new StaticFunc(4);
		System.out.println("----------");
		new StaticFunc(5);
	}
}
