/**
1、饿汉式：在程序启动或单件模式类被加载的时候，单件模式实例就已经被创建。
2、懒汉式：当程序第一次访问单件模式实例时才进行创建。
如何选择：如果单件模式实例在系统中经常会被用到，饿汉式是一个不错的选择。
懒汉模式在使用时，容易引起不同步问题，所以应该创建同步"锁"
*/

//饿汉式
/*
class Single
{
	private static final Single s = new Single();
	private Single(){}
	public static Single getInstance()
	{
		return s;
	}
}
*/

//懒汉式
class Single
{
	private static Single s = null;
	private Single(){}
	public static Single getInstance()
	{
		if(s==null)
		{
			synchronized(Single.class)
			{	
				if(s==null)
					s = new Single();
			}
		}
		return s;
	}
}

class SingleDemo
{
	public static void main(String[] args)
	{
		Single s = Single.getInstance();
	}
}
