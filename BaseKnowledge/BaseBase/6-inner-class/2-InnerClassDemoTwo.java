/**
方法中的内部类
*/

class Outer
{
	int x =3;
	
	void method(final int a)
	{
		final int y = 4;
		int z = 4;
		class Inner
		{
			void function()
			{
				System.out.println(Outer.this.x);
				System.out.println(x);
				System.out.println(y);
				System.out.println(z);
				System.out.println(a);
			}
		}
		new Inner().function();
	}
}

class InnerClassDemoTwo
{
	public static void main(String[] args)
	{
		Outer out = new Outer();
		out.method(7);
		System.out.println("---------------------------------");
		out.method(8);
	}
}
