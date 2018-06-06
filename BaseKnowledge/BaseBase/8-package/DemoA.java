/**
               public     protected      default     private
同一个类中     ok         ok             ok          ok
同一个包中     ok         ok             ok
子类           ok         ok             
不同包中       ok
*/

package packa;
public class DemoA extends packb.DemoB
{
	public void show()
	{
		a();
		System.out.println("DemoA");
		showb();
	}
	public void a()
	{
		System.out.println("a?");
	}
}
