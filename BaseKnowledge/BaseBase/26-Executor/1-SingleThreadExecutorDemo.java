/**
JAVA通过Executors提供了四种线程池，
单线程化线程池(newSingleThreadExecutor)、
可控最大并发数线程池(newFixedThreadPool)、
可回收缓存线程池(newCachedThreadPool)、
支持定时与周期性任务的线程池(newScheduledThreadPool)。
*/

/*单线程化线程池(newSingleThreadExecutor)的优点，串行执行所有任务。如果这个唯一的线程因为异常结束，那么会有一个新的线程来替代它。
此线程池保证所有任务的执行顺序按照任务的提交顺序执行*/

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
 
class ThreadPoolByNewSingleThreadExecutorDemo1 {
 
	public static void main(String[] args) {
		/**
		 * 单线程化的线程池
		 */
		ExecutorService singleThreadExecutor = Executors.newSingleThreadExecutor();
		for (int i = 0; i < 10; i++) {
			final int index = i;
			singleThreadExecutor.execute(new Runnable() {
				@Override
				public void run() {
					Thread.currentThread().setName("Thread i = " + index);
					System.out.println(Thread.currentThread().getName() + " index = " + index);
					try {
						Thread.sleep(500);
					} catch (InterruptedException e) {
						System.out.println("ssss");
					}
				}
			});
		}
		singleThreadExecutor.shutdown();
		System.out.println("on the main thread...");
	}
}

