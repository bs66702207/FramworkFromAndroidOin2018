import java.util.*;

class InstanceofTest
{
	public static void main(String[] args)
	{
		int i = 1;
		Object o = i;
		if(o instanceof Integer)
			System.out.println("o instanceof Integer");
		if(o instanceof Integer[])
			System.out.println("o instanceof Integer[]");
		Integer[] j = new Integer[1];
		Object oo = j;
		if(oo instanceof Integer)
			System.out.println("oo instanceof Integer");
		if(oo instanceof Integer[])
			System.out.println("oo instanceof Integer[]");

	}
}
