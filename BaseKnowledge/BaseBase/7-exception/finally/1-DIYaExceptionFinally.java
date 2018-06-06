class FuShuException extends RuntimeException
{
	private int value;
	FuShuException(String msg, int value)
	{
		super(msg);
		this.value = value;
	}
	public int getValue()
	{
		return value;
	}
}
class Demo 
{
	int div(int a, int b) throws FuShuException
	{
		if(b<0)
			throw new FuShuException("Negative /by fushu", b);//throw抛出自定义对象
		
		return a/b;
	}
}
class ExceptionFinally
{

	public static void main(String[] args)
	{
		Demo d= new Demo();
		try
		{
			int x = d.div(4, -1);
			System.out.println("x="+x);
		}
		catch(FuShuException e)
		{
			System.out.println(e.toString());
			System.out.println("Nagative:"+e.getValue());
			return;
		}
		finally
		{
			System.out.println("finally");
		}
		System.out.println("over");
	}
}