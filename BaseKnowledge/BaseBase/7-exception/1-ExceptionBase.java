class Demo
{
	int div(int a, int b) throws Exception//在功能上通过throws的关键字声明了该功能有可能会出现问题
	{
		return a/b;
	}
}

class ExceptionBase
{

	public static void main(String[] args)
	{
		Demo d= new Demo();
		try//需要被检测的代码，如果出现异常，jvm会产生new一个针对性异常，被try检测到，丢给e，跳转到catch，try中余下的语句不再执行
		{
			int x = d.div(4, 0);
			System.out.println("x="+x);
		}
		catch (Exception e)//Exception e = new ArithmeticException();
		{
			System.out.println("dived 0 !");
			System.out.println(e.getMessage());
			System.out.println(e.toString());//异常名称，异常信息
			e.printStackTrace();//异常名称，异常信息，异常位置;该方法是jvm的默认处理方法
		}
		finally//一定会执行的语句，并非必须加上finally
		{
			System.out.println("I have to clean something!");
		}
		System.out.println("over");
	}
}
