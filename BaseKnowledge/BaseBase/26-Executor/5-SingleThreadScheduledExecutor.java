//相对于Timer，这个的显著优势是线程池

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.ThreadFactory;
import java.util.concurrent.ScheduledExecutorService;

class newSingleThreadScheduledExecutor5{

	static Runnable task1 = new Runnable() {
		@Override
		public void run() {
			System.out.println("task1 runned");
			try {
				Thread.sleep(3000);
			} catch (InterruptedException e) {
				System.out.println("ssss");
			}
		}
	};
 
	static Runnable task2 = new Runnable() {
		@Override
		public void run() {
			System.out.println("task2 runned");
			try {
				Thread.sleep(600);
			} catch (InterruptedException e) {
				System.out.println("ssss");
			}
		}
	};

	static Runnable task3 = new Runnable() {
		@Override
		public void run() {
			System.out.println("task3 runned");
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				System.out.println("ssss");
			}
		}
	};

	public static void main(String[] args) {

	   	ThreadFactory t = new ThreadFactory() {
			@Override
			public Thread newThread(Runnable r) {
				Thread t = new Thread(r, "batterystats-worker");
				t.setPriority(Thread.NORM_PRIORITY);
				return t;
			}
		};
	
		ScheduledExecutorService mExecutorService = Executors.newSingleThreadScheduledExecutor(t);
	
		mExecutorService.schedule(task1, 0, TimeUnit.MILLISECONDS);
		mExecutorService.submit(task2);
		mExecutorService.submit(task3);
		try {
			Thread.sleep(500);
		} catch (InterruptedException e) {
			System.out.println("ssss");
		}

		System.out.println("on the main thread...");
	}
 
}
