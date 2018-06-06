/**
多线程的同步
1.操作共享数据的线程是否是两个以上且是否同步，synchronized
2.是否用了同一个锁synchronized(同一个锁)

wait();notify();notifyAll();都使用在synchronized中，因为要对持有监视器(锁)的线程操作。
只有同一个锁上的被等待线程，可以被同一个锁上的notify唤醒，即等待和唤醒必须是同一个锁。
代码见InputOutputDemo.java；优化代码--把调用时需要synchronized关键字去修饰函数，这样调用就变得简单得多，代码已经在本文件优化完了
*/

class Res
{
	private String name;
	private String sex;
	private boolean flag = false;
	public synchronized void set(String name, String sex)
	{
		if(flag)
			try{this.wait();}catch(Exception e){}
		this.name = name;
		this.sex = sex;
		flag = true;
		this.notify();
	}
	public synchronized void out()
	{
		if(!flag)
			try{this.wait();}catch(Exception e){}
		System.out.println(name+"..."+sex);
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
		int x =0;
		while(true)
		{
			if(x==0)
				r.set("mike", "man");
			else
				r.set("丽丽", "女女女女女");
			x = (x+1)%2;
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
