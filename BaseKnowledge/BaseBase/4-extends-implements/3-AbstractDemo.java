//抽象类里可以有非抽象方法。
abstract class Student
{
	abstract void study();
	void sleep()
	{
		System.out.println("zzz");
	}
}

class ChongCiStudent extends Student
{
	void study()
	{
		System.out.println("chongci study");
	}
}

class BaseStudent extends Student
{
	void study()
	{
		System.out.println("base study");
	}
}

class AdvBaseStudent extends Student
{
	void study()
	{
		System.out.println("adv study");
	}
}

class AbstractDemo 
{
	public static void main(String[] args)
	{
	//	Student S = new Student();//error
		BaseStudent BS = new BaseStudent();
		AdvBaseStudent ABS = new AdvBaseStudent();
		new BaseStudent().study();
		new BaseStudent().study();
		BS.study();
		ABS.study();
	//	S.sleep();
	}
}
