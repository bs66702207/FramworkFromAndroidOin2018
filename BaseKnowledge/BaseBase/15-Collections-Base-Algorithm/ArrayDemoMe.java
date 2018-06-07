import java.util.*;

class ArrayDemoMe
{
	public static void main(String[] args)
	{
		//int[] arr = {2,4,5};
		//System.out.println(Arrays.toString(arr));
		
		String[] arr = {"abc","cc","kkkk"};
		List<String> list = Arrays.asList(arr);
		//sop("contains:"+list.contains("cc"));
		//sop(list);
		
		//int[] nums = {2,4,5};
		//List<int[]> li = Arrays.asList(nums);
		
		Integer[] nums = {2,4,5};
		List<Integer> li = Arrays.asList(nums);
		sop(li);
	}
	
	public static boolean myContains(String[] arr,String key)
	{
		for(int x=0;x<arr.length; x++)
		{
			if(arr[x].equals(key))
				return true;
		}
		return false;
	}
	
	public static void sop(Object obj)
	{
		System.out.println(obj);
	}
}