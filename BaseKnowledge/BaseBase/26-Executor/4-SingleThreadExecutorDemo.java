/*如果这个任务正在等待执行者获取执行它的线程，那么这个任务将被取消而且不会开始他的执行。
如果这个任务已经正在运行，则视方法的参数情况而定。
cancel()方法接收一个Boolean值参数。
如果参数为true并且任务正在运行，那么这个任务将被取消。
如果参数为false并且任务正在运行，那么这个任务将不会被取消。
*/
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.ThreadFactory;
import java.util.concurrent.Future;

//cancel

class ThreadPoolByNewSingleThreadExecutorDemo4 {

	static Runnable task1 = new Runnable() {
		@Override
		public void run() {
			System.out.println("task1 runned start");
			try {
				Thread.sleep(5000);
			} catch (InterruptedException e) {
				System.out.println("ssss");
			}
			System.out.println("task1 runned end");
		}
	};
 
	static Runnable task2 = new Runnable() {
		@Override
		public void run() {
			System.out.println("task2 runned start");
			try {
				Thread.sleep(5000);
			} catch (InterruptedException e) {
				System.out.println("ssss");
			}
			System.out.println("task2 runned end");
		}
	};

	static Runnable task3 = new Runnable() {
		@Override
		public void run() {
			System.out.println("task3 runned start");
			try {
				Thread.sleep(5000);
			} catch (InterruptedException e) {
				System.out.println("ssss");
			}
			System.out.println("task3 runned end");
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
	
		ExecutorService mExecutorService = Executors.newSingleThreadExecutor(t);
	
		Future f1 = mExecutorService.submit(task1);
		Future f2 = mExecutorService.submit(task2);
		Future f3 = mExecutorService.submit(task3);

		System.out.println(f1.toString() + f2.toString() + f3.toString());

		try {
			Thread.sleep(100);
		} catch (InterruptedException e) {
			System.out.println("ssss");
		}

		f1.cancel(true);
		f2.cancel(false);
		f3.cancel(true);

		System.out.println("on the main thread...");
	}
}
