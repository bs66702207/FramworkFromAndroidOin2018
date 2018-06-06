/**
原来线程都有自己默认的名称。
Thread-编号 该编号从0开始。
static Thread currentThread():获取当前线程对象。
getName(): 获取线程名称。
设置线程名称：setName或者构造函数。
*/

class Test extends Thread
{
	//private String name;
	Test(String name)
	{
		//this.name = name;
		super(name);
	}
	public void run()
	{
		for(int x=0; x<60; x++)
		{
			//System.out.println(this.getName()+"---run---"+x);
			System.out.println(Thread.currentThread().getName()+"---run---"+x);
		}
	}
}

class GetThreadName
{
	public static void main(String[] args)
	{
		Test t1 = new Test("t-one");
		Test t2 = new Test("t-two");
		t1.start();
		t2.start();
		
		for(int x=0; x<60; x++)
			System.out.println("main--run---"+x);
	}
}
