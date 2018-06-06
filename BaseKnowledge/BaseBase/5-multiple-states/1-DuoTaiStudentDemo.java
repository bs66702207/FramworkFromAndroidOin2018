abstract class Student
{
	public abstract void study();
	public void sleep()
	{
		System.out.println("躺着睡");
	}
}

class BaseStudent extends Student
{
	public void study()
	{
		System.out.println("base study");
	}
	public void sleep()
	{
		System.out.println("坐着睡");
	}
}

class AdvStudent extends Student
{
	public void study()
	{
		System.out.println("Adv study");
	}
}

class DoStudent
{
	public void doSome(Student stu)
	{
		stu.study();
		stu.sleep();
	}
}

class DuoTaiStudentDemo
{
	public static void main(String[] args)
	{
		DoStudent ds = new DoStudent();
		ds.doSome(new BaseStudent());
		ds.doSome(new AdvStudent());
	}
}
