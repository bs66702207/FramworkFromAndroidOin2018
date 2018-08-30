abstract class Outer
{
	public int i;
	public abstract void sop(String msg);

	public static Outer getDefault() {
		return new Inner();
	}

	private static class Inner extends Outer{
		@Override
		public void sop(String msg) {
			System.out.println("msg " + msg);
		}
	}
}

class StaticInnerClassDemo
{
	public static void main(String[] args)
	{
		Outer oi1 = Outer.getDefault();
		Outer oi2 = Outer.getDefault();
		oi1.i = 1;

		System.out.println(oi1);
		System.out.println(oi2);
		System.out.println(oi1.i);
		System.out.println(oi2.i);
	}
}
