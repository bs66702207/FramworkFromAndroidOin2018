import java.util.concurrent.locks.*;

class lockDemo
{
	public static void main(String[] args)
	{
		Lock lock = new ReentrantLock();
		lock.lock();
		System.out.println("1");
		lock.lock();
		System.out.println("2");
		lock.unlock();
		lock.unlock();
	}
}
