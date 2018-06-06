/**
升级版的锁--显示的锁机制
jdk1.5新特性，以前程序员很苦比
synchronized是隐式的锁，锁住和解锁都是隐式的；而Lock，即显式的锁java.util.concurrent.locks的接口Lock；
此外，Condition也将Object 监视器方法进行了改动，await(wait)、signal(notify)、signalAll(notifyAll)。
private Condition condition_pro =lock.newCondition();
private Condition condition_con =lock.newCondition();
condition_pro.await();condition_con.await();
condition_pro.signal(); condition_con.signal();
从代码上可以看出，可以进行有目标的唤醒了。
*/

import java.util.concurrent.locks.*;

class ProducterConsumerNewLock
{
	public static void main(String[] args)
	{
		Resource r = new Resource();
		
		Producter pro = new Producter(r);
		Consumer con = new Consumer(r);
		Thread t1 = new Thread(pro);
		Thread t2 = new Thread(pro);
		Thread t3 = new Thread(con);
		Thread t4 = new Thread(con);
		
		t1.start();
		t2.start();
		t3.start();
		t4.start();
	}
}

class Resource
{
	private String name;
	private int count = 1;
	private boolean flag =false;
	
	private Lock lock = new ReentrantLock();
	
	private Condition condition_pro =lock.newCondition();
	private Condition condition_con =lock.newCondition();
	
	//t1 t2
	public void set(String name) throws InterruptedException
	{
		lock.lock();//锁
		try
		{
			while(flag)
				condition_pro.await();
			this.name = name+"--"+count++;
		
			System.out.println(Thread.currentThread().getName()+"...生产者..."+this.name);
			flag = true;
		
			condition_con.signal();
		}	
		finally
		{
			lock.unlock();//解锁
		}
	}
	
	//t3 t4
	public void out() throws InterruptedException
	{
		lock.lock();
		try
		{
			while(!flag)
				condition_con.await();
			System.out.println(Thread.currentThread().getName()+"...消费者......"+this.name);
			flag = false;
			condition_pro.signal();
		}
		finally
		{
			lock.unlock();
		}
		
	}
}

class Producter implements Runnable
{
	private Resource res;
	
	Producter(Resource res)
	{
		this.res = res;
	}
	public void run()
	{
		while(true)
		{
			try
			{
				res.set("+商品+");
			}
			catch (InterruptedException e)
			{
			}
		}
	}
}

class Consumer implements Runnable
{
	private Resource res;
	
	Consumer(Resource res)
	{
		this.res = res;
	}
	public void run()
	{
		while(true)
		{
			try
			{
				res.out();
			}
			catch (InterruptedException e)
			{
			}
		}
	}
}
