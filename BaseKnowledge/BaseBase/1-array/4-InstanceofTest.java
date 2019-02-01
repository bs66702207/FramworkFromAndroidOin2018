import java.util.*;

class InstanceofTest
{
	public static void main(String[] args)
	{
		int i = 1;
		Object o = i;
		System.out.println(o instanceof Integer);
		System.out.println(o instanceof Integer[]);
	}
}
