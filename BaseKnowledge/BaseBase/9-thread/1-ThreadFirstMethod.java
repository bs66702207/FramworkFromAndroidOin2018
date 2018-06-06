/**
(1)定义类继承Thread
(2)复写Thread类中的run方法
(3)调用线程的start方法，该方法有两个作用：启动线程、调用run方法。
*/

class Demo extends Thread
{
	public void run()
	{
		for(int x=0; x<60; x++)
		System.out.println("demo run---"+x);
	}
}

class ThreadFirstMethod
{
	public static void main(String[] args)
	{
		Demo d = new Demo();//建立好一个对象就创建好一个线程
		d.start();//执行线程
		
		//for(int x=0; x<60; x++)
		//	System.out.println("hello world!---"+x);
			
		Thread t = new Thread();
		t.start();
	}
}
