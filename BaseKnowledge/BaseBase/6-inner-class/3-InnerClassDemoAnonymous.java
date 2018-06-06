/**
匿名内部类的格式: new 父类或者接口(){定义子类的内容}，下面的abc()其实没有什么意义，建立匿名内部类目的就是简化书写，不是加方法用的
另外，匿名内部类方法1~2个，如果太多就失去简洁的目的，导致匿名内部类太胖，代码阅读性差
*/

abstract class AbsDemo
{
	abstract void show();
}

class Outer
{
	int x =3;
	
	/*class Inner extends AbsDemo
	{
		void show()
		{
			System.out.println("show: "+x);
		}
	}*/
	
	public void function()
	{
		//new Inner().show();
		
		new AbsDemo()
		{
			int num = 9;
			void show()
			{
				System.out.println("x1="+x);
				System.out.println("num="+num);
			}
			void abc()
			{
				System.out.println("haha1");
			}
		}.show();
		
		new AbsDemo()
		{
			void show()
			{
				System.out.println("x2="+x);
			}
			void abc()
			{
				System.out.println("haha2");
			}
		}.abc();
	}
}

class InnerClassDemoAnonymous
{
	public static void main(String[] args)
	{
		new Outer().function();
	}
}
