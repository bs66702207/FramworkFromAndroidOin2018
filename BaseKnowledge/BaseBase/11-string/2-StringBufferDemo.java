/**
StringBuffer
StringBuffer是字符串缓冲区，是一个容器，可存储、删除、获取、修改CURD create update read delete；
长度可变化，可以字节操作多个数据类型，最终会通过toString()方法变成字符串。
(1)存储
  StringBuffer append():将指定数据作为参数添加到已有数据结尾处。
  StringBuffer insert(index,数据):可以将数据插入到指定index位置。
(2)删除
  StringBuffer delete(start,end):删除缓冲区中的数据，包含start，不包含end。
  StringBuffer deleteCharAt(index):删除指定位置的字符。
  java规则之一：字符串索引传参内部引用，字符串从指定的 start 处开始，一直到索引 end - 1 处的字符
(3)获取
  char charAt(int index) 
  int indexOf(String str) 
  int lastIndexOf(String str) 
  int length() 
  String substring(int start, int end) 
(4)修改。
  StringBuffer replace(start,end,string);
  void setCharAt(int index, char ch) ;
(5)反转。
  StringBuffer reverse();
(6)将缓冲区中指定数据存储到指定字符数组中。
  void getChars(int srcBegin, int srcEnd, char[] dst, int dstBegin) 
*/

class StringBufferDemo
{
	public static void main(String[] args)
	{
		//method_update();
		//method_del();
		StringBuffer sb = new StringBuffer("abcdef");
		
		char[] chs = new char[4];
		
		sb.getChars(1,4,chs,1);
		for(int x=0; x<chs.length;x++)
		{
			sop("chs["+x+"]="+chs[x]+";");
		}
	}

	public static void method_update()
	{
		StringBuffer sb  = new StringBuffer("abcde");

	//	sb.replace(1,4,"java");
		sb.setCharAt(2,'k');


		sop(sb.toString());
	
	}
	
	public static void method_del()
	{
		StringBuffer sb = new StringBuffer("abcde");
		//sb.delete(1,3);
		sb.deleteCharAt(2);
		//清空缓冲区。
		//sb.delete(0,sb.length());
		sop(sb.toString());
	}
	
	public static void method_add()
	{
		StringBuffer sb = new StringBuffer();
		StringBuffer sb1 = sb.append("abc").append(true).append(34);
		sb.insert(1,"qq");
		sop("sb==sb1:"+(sb==sb1));
		sop(sb.toString());
		sop(sb1.toString());
	}
	
	public static void sop(String str)
	{
		System.out.println(str);
	}
}
