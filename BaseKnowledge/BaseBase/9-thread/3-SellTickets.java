/**
解决多线程卖100张票问题，问题关键点是开启四个线程进行卖票，但是只有100张票，如何保证其他线程知道第几座的票已售出，而不会卖出重复座位的票，资源独立、共享。
步骤：
(1)定义类实现Runnable接口
(2)覆盖Runnable接口中的run方法——线程执行的代码
(3)通过Thread类建立线程对象
(4)将Runnable接口的子类对象作为实际参数传递给Thread类的构造函数——为了让线程去执行指定对象的run方法。
(5)调用Thread类的start方法开启线程并调用Runnable接口子类的run方法
*/

class Ticket implements Runnable//extends Thread
{
	private int tick = 100;
	Object obj = new Object();
	public void run()
	{
			while(true)
			{
				synchronized(obj)//防止资源冲突
				{
					if(tick>0)
					{
						try{Thread.sleep(10);}catch(Exception e){}
						System.out.println(Thread.currentThread().getName() + "sale : " + tick--);
					}
				}
			}
	}
}

class SellTickets
{

	public static void test() {
		System.out.println("test!");
	}

	public static void addRunable(Runnable r) {
		System.out.println("addRunable!");
	}

	public static void main(String[] args)
	{
		Ticket t = new Ticket();
		Thread t1 = new Thread(t);
		Thread t2 = new Thread(t);
		Thread t3 = new Thread(t);
		Thread t4 = new Thread(t);
		t1.start();
		t2.start();
		t3.start();
		t4.start();

		Thread lambda = new Thread(() -> test());
		lambda.run();

		addRunable( ()-> {
			test();
			test();
		});
		
	}
}
