/**
Future接口主要包括5个方法
package java.util.concurrent;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

public interface Future<V> {
	//用来停止一个任务，如果任务可以停止（通过mayInterruptIfRunning来进行判断），则可以返回true,如果任务已经完成或者已经停止，或者这个任务无法停止，则会返回false
	boolean cancel(boolean var1);
	boolean isCancelled();//判断当前方法是否取消
	boolean isDone();//判断当前方法是否完成
	V get() throws InterruptedException, ExecutionException;//可以当任务结束后返回一个结果，如果调用时，工作还没有结束，则会阻塞线程，直到任务执行完毕
	V get(long var1, TimeUnit var3) throws InterruptedException, ExecutionException, TimeoutException;//加入timeout等待
}
*/

/*
	举个例子：比如去吃早点时，点了包子和凉菜，包子需要等3分钟，凉菜只需1分钟，如果是串行的一个执行，在吃上早点的时候需要等待4分钟，但是因为你在等包子的时候，
可以同时准备凉菜，所以在准备凉菜的过程中，可以同时准备包子，这样只需要等待3分钟。那Future这种模式就是后面这种执行模式。
*/

import java.util.concurrent.*;

class FutureDemo {

	public static void main(String[] args) throws InterruptedException, ExecutionException {
		long start = System.currentTimeMillis();

		// 等包子 -- 必须要等待返回的结果，所以要调用join方法
		Callable ca2 = new Callable() {
			@Override
			public Object call() throws Exception {
				try {
					Thread.sleep(1000*3);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				return "包子准备完毕";
			}
		};
		FutureTask<String> ft2 = new FutureTask<String>(ca2);
		new Thread(ft2).start();
		
		// 等凉菜 
		Callable ca1 = new Callable() {
			@Override
			public String call() throws Exception {
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				return "凉菜准备完毕";
			}
		};
		FutureTask<String> ft1 = new FutureTask<String>(ca1);
		new Thread(ft1).start();
		
		System.out.println(ft1.get());
		System.out.println(ft2.get());
		
		long end = System.currentTimeMillis();
		System.out.println("准备完毕时间："+(end-start));
	}

}
