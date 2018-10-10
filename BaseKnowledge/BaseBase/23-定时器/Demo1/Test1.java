import java.util.Date;
import java.util.Timer;

public class Test1 {

	public static void main(String[] args) {
		Timer timer = new Timer();
		OneTask task1 = new OneTask(1);
		OneTask task2 = new OneTask(2);
		OneTask task3 = new OneTask(3);

		System.out.println("start in main thread..." + Thread.currentThread().getId() + "name:" + Thread.currentThread().getName());
if(1 == 0) {

		timer.schedule(new OneTask(1), 5000);// 5秒后启动任务

		OneTask secondTask= new OneTask(2);
		timer.schedule(secondTask, 1000, 3000);// 1秒后启动任务,以后每隔3秒执行一次线程

		Date date = new Date();
		timer.schedule(new OneTask(3), new Date(date.getTime()+1000));//以date为参数，指定某个时间点执行线程

		//timer.cancel();
		//secondTask.cancel();

} else {

		timer.schedule(task1, 1000, 1000);// 1秒后启动任务,以后每隔1秒执行一次线程
		timer.schedule(task2, 2000, 2000);// 1秒后启动任务,以后每隔2秒执行一次线程
		timer.schedule(task3, 3000, 3000);// 1秒后启动任务,以后每隔3秒执行一次线程

}
/*
		try{Thread.sleep(10000);}catch(InterruptedException e){e.printStackTrace();}
		timer.cancel();
		System.out.println("cancel timer");
*/

/*
		try{Thread.sleep(10000);}catch(InterruptedException e){e.printStackTrace();}
		task1.cancel();
		System.out.println("cancel task1");

		try{Thread.sleep(10000);}catch(InterruptedException e){e.printStackTrace();}
		task2.cancel();
		System.out.println("cancel task2");

		try{Thread.sleep(10000);}catch(InterruptedException e){e.printStackTrace();}
		task3.cancel();
		System.out.println("cancel task3");
*/
		try{Thread.sleep(100000);}catch(InterruptedException e){e.printStackTrace();}
		timer.cancel();//这个重要必须cancel！
		System.out.println("end in main thread...");
	}
}
