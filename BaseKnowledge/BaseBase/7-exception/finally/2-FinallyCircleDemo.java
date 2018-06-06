/**
存放一定会执行的代码，finally有一个非常重要的应用，就是关闭数据库连接，即释放资源。
System.exit(0); 这个语句如果与finally之前执行，即jvm结束，finally是不会执行的。
*/

class NoValueException extends RuntimeException
{
	NoValueException(String message)
	{
		super(message);
	}
}

interface Shape
{
	void getArea();
}

class Rec implements Shape
{
	private int len,wid;
	
	Rec(int len, int wid) //throws NoValueException
	{
		if(len<=0 || wid<=0) 
			throw new NoValueException("出现非法值");
		this.len = len;
		this.wid = wid;
	}
	
	public void getArea()
	{
		System.out.println(len*wid);
	}
}

class Circle implements Shape
{
	private int radius;
	public static final double PI = 3.14;
	Circle(int radius)
	{
		if(radius<=0)
			throw new NoValueException("半径非法");
		this.radius = radius;
	}
	
	public void getArea()
	{
		System.out.println(radius*radius*PI);
	}
}

class FinallyCircleDemo
{
	public static void main(String[] args)
	{
		try
		{
			Rec r = new Rec(-3, 4);
			r.getArea();
		}
		catch (NoValueException e)
		{
			throw e;
			//System.out.println(e.toString());
			//System.exit(0);
		}
		finally
		{
			System.out.println("finally");
		}
		
		//Circle c= new Circle(-8);
		//System.out.println("over");
	}
}
