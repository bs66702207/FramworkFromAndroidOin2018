//方法非runtime类，有抛即要有解决，哪怕是自己的方法内进行try，catch，都是一样的
class Demo
{
	public void method() 
	{
		try
		{
			throw new Exception();
		}
		catch (Exception e)
		{
			throw e; 
		}
		finally 
		{
			//关资源，或者是必须需要执行的代码
		}
	}
}

class NoRuntimeException
{
	public static void main(String[] args)
	{
		System.out.println("Hello World!");
	}
}
