class Fu
{
	Fu()
	{
		System.out.println("fu run");
	}

	Fu(int x)
	{
		System.out.println("fu run" + x);
	}
}

class Zi extends Fu
{
	Zi()
	{
		System.out.println("Zi run");
	}

	Zi(int x)
	{
		super(x);//如果没有这个，则调用Fu()
		System.out.println("Zi run"+x);
	}

}

class ExtendsDemo
{
	public static void main(String[] args)
	{
		Zi z = new Zi(1);
	}
}
