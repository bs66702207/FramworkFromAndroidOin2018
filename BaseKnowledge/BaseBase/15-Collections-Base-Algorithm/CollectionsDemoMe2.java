import java.util.*;

	class StrComparator implements Comparator<String>
	{
		public int compare(String s1,String s2)
		{
			/*
			int num = s1.compareTo(s2);
			if(num>0)
				return -1;
			if( num<0)
				return 1;
			return num;
			*/
		
			return s2.compareTo(s1);
		}
	}
	
	class StrLenComparator implements Comparator<String>
	{
		public int compare(String s1,String s2)
		{
			if(s1.length()>s2.length())
				return 1;
			if(s1.length()<s2.length())
				return -1;
			return s1.compareTo(s2);
		}
	}

class CollectionsDemoMe2
{
	public static void main(String[] args)
	{
		//fillDemo();
		//replaceAllDemo();
		//orderDemo();
		shuffleDemo();
	}
	
	public static void shuffleDemo()
	{
		List<String> list = new ArrayList<String>();

		list.add("abcd");
		list.add("aaa");
		list.add("zz");
		list.add("kkkkk");
		list.add("qq");
		list.add("z");

		sop(list);
		Collections.shuffle(list);
		sop(list);
	}
	
	public static void orderDemo()
	{	
		//TreeSet<String> ts = new TreeSet<String>();//默认自然排序
		//TreeSet<String> ts = new TreeSet<String>(new StrComparator());
		//TreeSet<String> ts = new TreeSet<String>(Collections.reverseOrder());//逆转自然顺序(默认比较器被逆转)
		//TreeSet<String> ts = new TreeSet<String>(new StrLenComparator());
		TreeSet<String> ts = new TreeSet<String>(Collections.reverseOrder(new StrLenComparator()));//逆转比较器顺序
		ts.add("abcde");
		ts.add("aaa");
		ts.add("k");
		ts.add("cc");

		Iterator it = ts.iterator();
		while(it.hasNext())
		{
			System.out.println(it.next());
		}
	}
	
	
	
	public static void replaceAllDemo()
	{
		List<String> list = new ArrayList<String>();
		list.add("abcd");
		list.add("aaa");
		list.add("zz");
		list.add("kkkkk");
		list.add("qq");
		list.add("z");
		sop(list);
		Collections.replaceAll(list, "aaa", "ak47");
		Collections.reverse(list);
		sop(list);
	}
	
	public static void fillDemo()
	{
		List<String> list = new ArrayList<String>();
		list.add("abcd");
		list.add("aaa");
		list.add("zz");
		list.add("kkkkk");
		list.add("qq");
		list.add("z");
		sop(list);
		Collections.fill(list, "pp");
		sop(list);
	}
	
	public static void sop(Object obj)
	{
		System.out.println(obj);
	}
}