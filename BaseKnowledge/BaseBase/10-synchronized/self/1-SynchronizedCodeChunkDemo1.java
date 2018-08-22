/**
synchronized是Java中的关键字，是一种同步锁。它修饰的对象有以下几种：
1.修饰一个代码块，被修饰的代码块称为同步语句块，其作用的范围是大括号{}括起来的代码，作用的对象是调用这个代码块的对象；
2.修饰一个方法，被修饰的方法称为同步方法，其作用的范围是整个方法，作用的对象是调用这个方法的对象；
3.修改一个静态的方法，其作用的范围是整个静态方法，作用的对象是这个类的所有对象；
4.修改一个类，其作用的范围是synchronized后面括号括起来的部分，作用的对象是这个类的所有对象。
我们会建立多个Demo文件，来讲述上面的这些情况，这是Java多线程的基础
*/

//一个线程访问一个对象中的synchronized(this)同步代码块时，其他试图访问该对象的线程将被阻塞。
class SyncThread implements Runnable {
	private static int count;
	public SyncThread() {
		count = 0;
	}
	public void run() {
		synchronized(this) {
			for (int i = 0; i < 5; i++) {
				try {
					System.out.println(Thread.currentThread().getName() + ":" + (count++));
					Thread.sleep(100);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
	}

	public int getCount() {
		return count;
	}
}

class SynchronizedCodeChunkDemo1 {
	public static void main(String[] args) {
/*
	当两个并发线程(thread1和thread2)访问同一个对象(syncThread)中的synchronized代码块时，在同一时刻只能有一个线程得到执行，
另一个线程受阻塞必须等待当前线程执行完这个代码块以后才能执行该代码块。
	Thread1和thread2是互斥的，因为在执行synchronized代码块时会锁定当前的对象，只有执行完该代码块才能释放该对象锁，
下一个线程才能执行并锁定该对象。
*/
if(1 == 0) {
		SyncThread syncThread = new SyncThread();
		Thread thread1 = new Thread(syncThread, "SyncThread1");
		Thread thread2 = new Thread(syncThread, "SyncThread2");
		thread1.start();
		thread2.start();
}

//我们再把SyncThread的调用稍微改一下：
if(1 == 1) {
		Thread thread1 = new Thread(new SyncThread(), "SyncThread1");
		Thread thread2 = new Thread(new SyncThread(), "SyncThread2");
		thread1.start();
		thread2.start();
}
	}
}

/**
总结：
A.无论synchronized关键字加在方法上还是对象上，如果它作用的对象是非静态的，则它取得的锁是对象；
  如果synchronized作用的对象是一个静态方法或一个类，则它取得的锁是对类，该类所有的对象同一把锁。
B.每个对象只有一个锁（lock）与之相关联，谁拿到这个锁谁就可以运行它所控制的那段代码。
C.实现同步是要很大的系统开销作为代价的，甚至可能造成死锁，所以尽量避免无谓的同步控制。
*/
