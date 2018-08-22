/**
多线程的同步
1.操作共享数据的线程是否是两个以上且是否同步，synchronized
2.是否用了同一个锁synchronized(同一个锁)

wait();notify();notifyAll(); 都使用在synchronized中，因为要对持有监视器(锁)的线程操作。
只有同一个锁上的被等待线程，可以被同一个锁上的notify唤醒，即等待和唤醒必须是同一个锁。
代码见1-WaitNotifySyncDemo.java; 通过wait和notify进行set/out同步
*/

class Res
{
	private String name;
	private String sex;
	private boolean flag = false;
	public synchronized void set(String name, String sex)
	{
		if(flag)
			try{System.out.println("set: flag = " + flag +", need to wait");this.wait();}catch(Exception e){}
		else
			System.out.println("set: flag = " + flag +", do not need to wait");
		System.out.println("set: " + name + "..." + sex);
		this.name = name;
		this.sex = sex;
		flag = true;
		this.notify();
	}
	public synchronized void out()
	{
		if(!flag)
			try{System.out.println("out: flag = " + flag +", need to wait");this.wait();}catch(Exception e){}
		else
			System.out.println("out: flag = " + flag +", do not need to wait");
		System.out.println("out: "+ name + "..." + sex);
		flag = false;
		this.notify();
	}
}

class Input implements Runnable
{
	private Res r;
	
	Input(Res r)
	{
		this.r = r;
	}

	public void run()
	{
		int x = 0;
		int i = 0;
		while(true)
		{
			if(x==0)
				r.set("mike", "man"+i);
			else
				r.set("lili", "girl"+i);
			x = (x+1)%2;
			i++;
		}
	}
}

class Output implements Runnable
{
	private Res r;
	Output(Res r)
	{
		this.r = r;
	}	
	public void run()
	{
		while(true)
		{
			r.out();
		}
	}
}

class IntputOutputDemo
{
	public static void main(String[] args)
	{
		Res r = new Res();
		new Thread(new Input(r)).start();
		new Thread(new Output(r)).start();
	}
}

//notiftAll
