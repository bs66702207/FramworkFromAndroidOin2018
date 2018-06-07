/*
���󣺶�ѧ����������������������

��Ϊ�������Լ�ֵ����ʽ���ڵġ�
����Ҫʹ�ÿ��������Map���ϡ�TreeMap��
*/
import java.util.*;

class StuNameComparator implements Comparator<Student>
{
	public int compare(Student s1,Student s2)
	{
		int num = s1.getName().compareTo(s2.getName());
		if(num==0)
			return new Integer(s1.getAge()).compareTo(new Integer(s2.getAge()));

		return num;
	}
}


class  MapTest2
{
	public static void main(String[] args) 
	{
		TreeMap<Student,String> tm = new TreeMap<Student,String>();//(new StuNameComparator());
		//TreeMap<Student,String> tm = new TreeMap<Student,String>();//compareTo

		tm.put(new Student("a",23),"nanjing");
		tm.put(new Student("b",21),"beijing");
		tm.put(new Student("c",24),"wuhan");
		tm.put(new Student("e",21),"tianjin");
		tm.put(new Student("d",22),"shanghai");

		
		Set<Map.Entry<Student,String>> entrySet = tm.entrySet();

		Iterator<Map.Entry<Student,String>> it = entrySet.iterator();

		while(it.hasNext())
		{
			Map.Entry<Student,String> me = it.next();

			Student stu = me.getKey();
			String addr = me.getValue();
			System.out.println(stu+":::"+addr);
		}
	}
}
