class Demo 
{
	int div(int a, int b)throws ArithmeticException,ArrayIndexOutOfBoundsException 
	/*在功能上通过throws的关键字声明了该功能有可能会出现问题*/
	{
		int[] arr = new int[a];
		System.out.println(arr[4]);
		return a/b;
	}
}

class ThrowTwoException
{

	public static void main(String[] args)
	{
		Demo d= new Demo();
		try
		{
			int x = d.div(4, 0);
			System.out.println("x="+x);
		}
		catch (ArithmeticException e)
		{
			System.out.println(e.toString());
		}
		catch (ArrayIndexOutOfBoundsException e)
		{
			System.out.println(e.toString());
		}
		System.out.println("over");
	}
}
