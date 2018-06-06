//notifyAll使用方法

class ProducterConsumerDemo
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
	//t1 t2
	public synchronized void set(String name)
	{
		//if(flag) //只判断一次 t2唤醒后不会判断，而是直接“生产”
		while(flag)
			try{this.wait();}catch(Exception e){}
		this.name = name+"--"+count++;
		
		System.out.println(Thread.currentThread().getName()+"...生产者..."+this.name);
		flag = true;
		//this.notify();
		this.notifyAll();
	}
	
	//t3 t4
	public synchronized void out()
	{
		//if(!flag)
		while(!flag)
			try{this.wait();}catch(Exception e){}
		System.out.println(Thread.currentThread().getName()+"...消费者......"+this.name);
		flag = false;
		//this.notify();
		this.notifyAll();
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
			res.set("+商品+");
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
			res.out();
		}
	}
}
