Timer是一种线程设施，用于安排以后在后台线程中执行的任务。可安排任务执行一次，或者定期重复执行，可以看成一个定时器，可以调度TimerTask。
TimerTask是一个抽象类，实现了Runnable接口，所以具备了多线程的能力。

Timer里面有4个schedule重载函数。而且还有两个scheduleAtFixedRate：

void scheduleAtFixedRate(TimerTask task, Date firstTime, long period)
安排指定的任务在指定的时间开始进行重复的固定速率执行。
void scheduleAtFixedRate(TimerTask task, long delay, long period)
安排指定的任务在指定的延迟后开始进行重复的固定速率执行。

	使用scheduleAtFixedRate的话, Timer会尽量的让任务在一个固定的频率下运行。例如：在Test1例子中，让secondTask在1秒钟后，每3秒钟执行一次，
但是因为java不是实时的，所以，我们在上个程序中表达的原义并不能够严格执行，例如有时可能资源调度紧张4秒以后才执行下一次，有时候又3.5秒执行。
如果我们调用的是scheduleAtFixedRate，那么Timer会尽量让你的secondTask执行的频率保持在3秒一次。运行上面的程序，假设使用的是scheduleAtFixedRate，
那么下面的场景就是可能的：1秒钟后，secondTask执行一次，因为系统繁忙，之后的3.5秒后secondTask才得以执行第二次，然后Timer记下了这个延迟，并
尝试在下一个任务的时候弥补这个延迟，那么2.5秒后，secondTask将执行第三次。“以固定的频率而不是固定的延迟时间去执行一个任务”就是这个意思。

Timer终止的问题：

默认情况下，只要一个程序的timer线程在运行，那么这个程序就会保持运行。可以通过以下3种方法终止一个timer线程：
（1）调用timer的cancle方法。你可以从程序的任何地方调用此方法，甚至在一个timer task的run方法里；
（2）让timer线程成为一个daemon线程（可以在创建timer时使用new Timer(true)达到这个目地），这样当程序只有daemon线程的时候，它就会自动终止运行；
（3）调用System.exit方法，使整个程序（所有线程）终止。

TimerTask也有cancel方法。

	上面所说的“只要一个程序的timer线程在运行，那么这个程序就会保持运行”。那么反过来，如果Timer里的所有TimerTask都执行完了，整个程序会退出吗，
经测试答案是否定的，例如上面的测试代码，如果只加第一个TimerTask在Timer中执行：

timer.schedule(new OneTask(1), 5000);// 5秒后启动任务
那么5秒以后，其实整个程序还是没有退出，Timer会等待垃圾回收的时候被回收掉然后程序会得以退出，但是多长时间呢？

在TimerTask的run函数执行完以后加上System.gc();就可以了。
