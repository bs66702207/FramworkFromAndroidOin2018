class Outer
{
	private int a = 3;
	private static int x = 3;
	class Inner
	{
		void function()
		{
			System.out.println("innner static :x "+x+", inner :a "+a);
		}
	}
	
	class Inner2
	{
		void show()
		{
			new Inner().function();
			System.out.println("innner2 show");
		}
	}
	
	public void method()
	{
		//Inner.function();
		new Inner2().show();
	}
}

class StaticInnerClassDemo
{
	public static void main(String[] args)
	{
		new Outer().new Inner2().show();
	}
}
