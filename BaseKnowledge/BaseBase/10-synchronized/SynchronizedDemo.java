class TH implements Runnable
{

	static public Object mLock;

	TH() {
		mLock = new Object();
	}

    public void run()
    {
        while(true)
        {
			synchronized(mLock) {
				try {
					Thread.sleep(5000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
        }
    }
}


class SynchronizedDemo
{
	public static void main(String[] args)
	{
		TH mth = new TH();
//        new Thread(mth).start();
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		synchronized(mth.mLock) {
			System.out.println("1");
			synchronized(mth.mLock) {
				System.out.println("2");
				synchronized(mth.mLock) {
					System.out.println("3");
				}
			}
		}

	}
}
