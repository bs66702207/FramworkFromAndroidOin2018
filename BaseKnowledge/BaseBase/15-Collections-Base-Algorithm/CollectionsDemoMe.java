import java.util.*;

class CollectionsDemoMe
{
	public static void main(String[] args)
	{
		sortDemo();
		//maxDemo();
		//binarySearchDemo();
	}
	
	public static void binarySearchDemo()
	{
		List<String> list = new ArrayList<String>();
		list.add("abcd");
		list.add("aaa");
		list.add("zz");
		list.add("kkkkk");
		list.add("qq");
		list.add("z");
		//Collections.sort(list);
		Collections.sort(list, new StrLenComparator());
		sop(list);
		
		//int index = Collections.binarySearch(list, "aaa");
		//int index = halfSearch(list, "aaa");
		int index = halfSearch2(list,"kkkkk",new StrLenComparator());
		sop("index="+index);
	}
	
	public static int halfSearch2(List<String> list,String key, Comparator<String> cmp)
	{
		int max,min,mid;
		max = list.size()-1;
		min = 0;

		while(min<=max)
		{
			mid = (max+min)>>1;//  /2;

			String str = list.get(mid);

			int num = cmp.compare(str, key);
			if(num>0)
				max = mid -1;
			else if(num<0)
				min = mid + 1;
			else
				return mid;
		}
		return -min-1;
	}
	
	public static int halfSearch(List<String> list,String key)
	{
		int max,min,mid;
		max = list.size()-1;
		min = 0;

		while(min<=max)
		{
			mid = (max+min)>>1;//  /2;

			String str = list.get(mid);

			int num = str.compareTo(key);
			if(num>0)
				max = mid -1;
			else if(num<0)
				min = mid + 1;
			else
				return mid;
		}
		return -min-1;
	}
	
	public static void maxDemo()
	{
		List<String> list = new ArrayList<String>();
		list.add("abcd");
		list.add("aaa");
		list.add("zz");
		list.add("kkkkk");
		list.add("qq");
		list.add("z");
		Collections.sort(list);
		sop(list);
		//String max = Collections.max(list);
		String max = Collections.max(list, new StrLenComparator());
		sop("max="+max);
	}
	
	public static void sortDemo()
	{
		List<String> list = new ArrayList<String>();
		list.add("abcd");
		list.add("aaa");
		list.add("zz");
		list.add("kkkkk");
		list.add("qq");
		list.add("z");
		sop(list);
		
		//Collections.sort(list);
		Collections.sort(list, new StrLenComparator());
		//Collections.swap(list, 0, 1);
		sop(list);
		
	}
	public static void sop(Object obj)
	{
		System.out.println(obj);
	}
}
class StrLenComparator implements Comparator<String>
{
	public int compare(String s1, String s2)
	{
		if(s1.length()>s2.length())
			return 1;
		if(s1.length()<s2.length())
			return -1;
		return s1.compareTo(s2);
	}
}
//public static <T extends Comparable<? super T>> void sort(List<T> list)