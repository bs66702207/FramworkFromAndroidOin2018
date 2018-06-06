/**
12.7 join
t1.join();——主线程挂起，t1获得cpu执行权，直到t1结束
12.8 优先级&yield方法
优先级1~10，通常需要1、5、10，jdk的Thread类中MAX_PRIOITY=10 MIN_PRIOITY=1 NORM_PRIOITY=5。
yield暂停当前正在执行的线程对象，并执行其他线程。
*/

class Demo implements Runnable
{
	public void run()
	{
		for(int x=0; x<70; x++)
		{
			System.out.println(Thread.currentThread().toString()+"......"+x);
	//		Thread.yield();
		}
	}
}
class JoinDemo
{
	public static void main(String[] args) throws Exception
	{
		Demo d = new Demo();
		Thread t1 = new Thread(d);
		Thread t2 = new Thread(d);
		t1.start();
		
		t1.setPriority(Thread.MAX_PRIORITY);
		
		t2.start();
		t1.join();
		for(int x=0; x<80; x++)
		{
			//System.out.println("main..."+x);
		}
		System.out.println("over");
	}
}
