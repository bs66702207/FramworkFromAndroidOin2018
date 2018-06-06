interface Smoking
{
	public abstract void smoke();
}

abstract class Student
{
	abstract void study();
	void sleep()
	{
		System.out.println("sleep");
	}
}

class Zhang3 extends Student implements Smoking
{
	void study(){}
	public void smoke(){}
}

class li4 extends Student
{
	void study(){}
}

class Sporter
{
	void play();
}

class TheEnd
{
	public static void main(String[] args)
	{

	}
}
