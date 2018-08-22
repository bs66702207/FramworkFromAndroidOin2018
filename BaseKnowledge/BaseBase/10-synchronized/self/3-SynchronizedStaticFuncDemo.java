//我们知道静态方法是属于类的而不属于对象的。同样的，synchronized修饰的静态方法锁定的是这个类的所有对象。
/**
 * 同步线程
 */
class SyncThread implements Runnable {
	private static int count;

	public SyncThread() {
		count = 0;
	}

	public synchronized static void method() {
		for (int i = 0; i < 5; i ++) {
			try {
				System.out.println(Thread.currentThread().getName() + ":" + (count++));
				Thread.sleep(100);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

	public synchronized void run() {
		method();
	}
}
//这个调用方式在1-SynchronizedCodeChunkDemo1中没用让thread1和thread2同步起来，但是这次就同步了
class SynchronizedStaticFuncDemo {
	public static void main(String[] args) {
		SyncThread syncThread1 = new SyncThread();
		SyncThread syncThread2 = new SyncThread();
		Thread thread1 = new Thread(syncThread1, "SyncThread1");
		Thread thread2 = new Thread(syncThread2, "SyncThread2");
		thread1.start();
		thread2.start();		
	}
}
