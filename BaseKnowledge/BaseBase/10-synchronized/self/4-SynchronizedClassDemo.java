//修饰一个类，其作用的范围是synchronized后面括号括起来的部分，作用的对象是这个类的所有对象
class SyncThread implements Runnable {
	private static int count;
	public SyncThread() {
		count = 0;
	}

	public static void method() {
		synchronized(SyncThread.class) {
			for (int i = 0; i < 5; i ++) {
				try {
					System.out.println(Thread.currentThread().getName() + ":" + (count++));
					Thread.sleep(100);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
	}

	public synchronized void run() {
		method();
	}
}

class SynchronizedClassDemo {
	public static void main(String[] args) {
		SyncThread syncThread1 = new SyncThread();
		SyncThread syncThread2 = new SyncThread();
		Thread thread1 = new Thread(syncThread1, "SyncThread1");
		Thread thread2 = new Thread(syncThread2, "SyncThread2");
		thread1.start();
		thread2.start();
	}
}
