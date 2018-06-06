class Demo
{
	private int num;
	Demo(int num)
	{
		this.num = num;
	}
	public boolean equals(Object d)
	{
		if(!(d instanceof Demo))
			return false;
		Demo x = (Demo) d;
		return this.num == x.num;
	}
	public String toString()
	{
		return "demo:"+num;
	}
}

class ObjectDemo
{
	public static void main(String[] args)
	{
		Object d1 = new Demo(4);
		
		System.out.println(Integer.toHexString(d1.hashCode()));
		System.out.println(d1.toString());
		System.out.println(d1.getClass().toString());
		System.out.println(d1.getClass().getName());
	}
}