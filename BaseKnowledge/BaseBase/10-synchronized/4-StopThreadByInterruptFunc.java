/**
线程进入冻结状态，主线程使用interrupt()方法将处于冻结状态的线程强制的恢复到运行状态；
这样run中的try/catch的catch就会捕捉异常，执行catch中的代码(里面可以操作标记让线程结束)。

守护线程setDaemon
必须等所有的Non-daemon线程都运行结束了，只剩下daemon的时候，JVM才会停下来，注意Main主程序是Non-daemon线程
*/

class StopThread implements Runnable
{
	private boolean flag = true;
	public synchronized void run()
	{
		while(flag)
		{
			try
			{
				//wait();
				Thread.sleep(1000);
			}
			catch(InterruptedException e)
			{
				System.out.println(Thread.currentThread().getName()+"...Exception");
				flag = false;
			}
			System.out.println(Thread.currentThread().getName()+"...run");
		}
	}
	public void changeFlag()
	{
		flag = false;
	}
}

class StopThreadByInterruptFunc
{
	public static void main(String[] args)
	{
		StopThread st = new StopThread();
		Thread t1 = new Thread(st);
		Thread t2 = new Thread(st);
		
		t1.setDaemon(true);
		t2.setDaemon(true);
		t1.start();
		t2.start();
		
		int num = 0;

		while(true)
		{
			if(num++ == 60)
			{
				//st.changeFlag();
				t1.interrupt();
				//t2.interrupt();
				break;
			}
			System.out.println(Thread.currentThread().getName()+"......"+num);
		}
		System.out.println("over");

	}

}
