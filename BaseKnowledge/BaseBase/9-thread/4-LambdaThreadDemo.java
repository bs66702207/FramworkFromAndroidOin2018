import java.util.LinkedList;

class LambdaThreadDemo
{

	public static LinkedList<Runnable> mQueues = new LinkedList<Runnable>();

	public static void test1() {
		System.out.println("test1!");
	}

	public static void test2() {
		System.out.println("test2!");
	}

	public static void addRunable(Runnable r) {

		mQueues.add(r);
		System.out.println("addRunable!");
	}

	public static void main(String[] args)
	{
		Thread lambda = new Thread(() -> test1());
		lambda.run();

		System.out.println("queue.size() before = " + mQueues.size());
if(0 == 0) {
		addRunable( () -> {
			test1();
			test2();
		});
} else {
		addRunable(() -> test1());
		addRunable(() -> test2());
}

		Runnable handler = null;
		handler = mQueues.removeFirst();
		handler.run();
		System.out.println("queue.size() after = " + mQueues.size());

	}
}
