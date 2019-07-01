
public class MethodRefDemo
{

    private static void func() {
        System.out.println("func!");
    }

	public static void main(String[] args)
	{
        Thread mLoopThread;
        mLoopThread = new Thread(MethodRefDemo::func, "MethodRefDemo");
        mLoopThread.start();
        while(true);
	}
}
