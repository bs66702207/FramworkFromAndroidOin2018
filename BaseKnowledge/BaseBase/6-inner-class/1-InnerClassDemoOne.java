/**
有名内部类，基本使用方式，内部类可以直接访问外部类中的成员xxx，包括私有；因为内部类中持有了外部类的引用，格式: 外部类名.this.xxx
*/

class Outer
{
	private static final int TEST_CODE = 0x5;
	int x = 3;
	class Inner
	{
		int x = 4;
		void function()
		{
			int x = 6;
			System.out.println("innner:x "+x);
			System.out.println("innner:this.x "+this.x);
			System.out.println("innner:Outer.this.x "+Outer.this.x);
			System.out.println("innner:Outer::TEST_CODE "+TEST_CODE);
		}
	}
	
	void method()
	{
		Inner in = new Inner();
		in.function();
	}
}

class InnerClassDemoOne
{
	public static void main(String[] args)
	{
		Outer out = new Outer();
		out.method();
		
		Outer.Inner in = new Outer().new Inner();
		in.function();
	}
}
