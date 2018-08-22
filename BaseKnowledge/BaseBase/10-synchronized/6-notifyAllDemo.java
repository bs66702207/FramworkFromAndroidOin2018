//notifyAll使用方法，notifyAll()就会释放所有的锁

class notifyAllDemo
{
	public static void main(String[] args)
	{
		Resource r = new Resource();
		
		Consumer con = new Consumer(r);
		Thread t1 = new Thread(con);
		Thread t2 = new Thread(con);
		Thread t3 = new Thread(con);
		Thread t4 = new Thread(con);
		
		t1.start();
		t2.start();
		t3.start();
		t4.start();
		
		try{Thread.sleep(5000);}catch(InterruptedException e){e.printStackTrace();}
		r.boardcast();
	}
}

class Resource
{
	public synchronized void print()
	{
		System.out.println(Thread.currentThread().getName() + "start");
		try{this.wait();}catch(Exception e){}
		System.out.println(Thread.currentThread().getName() + "end");
	}

	public synchronized void boardcast()
	{
		System.out.println("boardcast");
		this.notifyAll();
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
		try{Thread.sleep(10);}catch(InterruptedException e){e.printStackTrace();}
		res.print();
	}
}
