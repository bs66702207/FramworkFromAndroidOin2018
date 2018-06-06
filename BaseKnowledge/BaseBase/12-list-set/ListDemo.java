import java.util.*;
class ListDemo 
{
	public static void sop(Object obj)
	{
		System.out.println(obj);
	}

	public static void method()
	{
		ArrayList al = new ArrayList();
		al.add("java01");
		al.add("java02");
		al.add("java03");
		sop("原集合是："+al);
		
		al.add(1,"java09");
		
		//al.remove(2);
		
		//al.set(2,"java007");
		
		sop("get(1):"+al.get(1));
		sop(al);
		
		for(int x=0; x<al.size(); x++)
		{
			System.out.println("al("+x+")="+al.get(x));
		}
		
		Iterator it = al.iterator();

		while(it.hasNext())
		{
			sop("next:"+it.next());
		}
		
		sop("index="+al.indexOf("java02"));

		List sub = al.subList(1,3);

		sop("sub="+sub);
	}
	
	public static void main(String[] args) 
	{
		//演示列表迭代器。
		ArrayList al = new ArrayList();

		//添加元素
		al.add("java01");
		al.add("java02");
		al.add("java03");
		sop(al);
		ListIterator li = al.listIterator();

		
		//sop("hasPrevious():"+li.hasPrevious());//false

		while(li.hasNext())
		{
			Object obj = li.next();

			if(obj.equals("java02"))
				//li.add("java009");
				li.set("java006");


		}
		
		while(li.hasPrevious())
		{
			sop("pre::"+li.previous());
		}
		
		//sop("hasNext():"+li.hasNext());//false
		//sop("hasPrevious():"+li.hasPrevious());//true



		sop(al);
		
		
		
		/*
		//在迭代过程中，准备添加或者删除元素。

		Iterator it = al.iterator();
		sop(al);
		while(it.hasNext())
		{
			Object obj = it.next();

			if(obj.equals("java02"))
				//al.add("java008");//触发并发异常ConcurrentModificationException，迭代器在操作中，不能用集合操作 
				it.remove();//将java02的引用从集合中删除了。

			sop("obj="+obj);
		}
		sop(al);
		*/
	}
}