import java.util.*;

class LinkedListDemo 
{
	public static void main(String[] args) 
	{
		LinkedList link = new LinkedList();

		link.addLast("java01");
		link.addLast("java02");
		link.addLast("java03");
		link.addLast("java04");
		
		/*link.addFirst("java01");
		link.addFirst("java02");
		link.addFirst("java03");
		link.addFirst("java04");*/
		
		//sop(link);
		//sop(link.getFirst());
		//sop(link.getFirst());
		//sop(link.getLast());
		//sop(link.removeFirst());
		//sop(link.removeFirst());
		//sop("size="+link.size());
		
		while(!link.isEmpty())
		{
			sop(link.removeLast());
		}
	}

	public static void sop(Object obj)
	{
		System.out.println(obj);
	}
}