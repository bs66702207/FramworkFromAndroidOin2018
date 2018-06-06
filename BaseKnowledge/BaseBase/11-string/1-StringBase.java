/**
String s1 = "abc";
String s2 = new String("abc");
s1在内存中有一个对象；s2在内存中有两个对象。
常量池
String s1 = "abc";
String s2 = new String("abc");
String s3 = "abc";
System.out.println(s1==s2); false
System.out.println(s1==s3); true
System.out.println(s1.equals(s2)); true
说明，abc在常量池中，s3指向abc，所以s1==s3
*/

class StringBase
{
	public static void main(String[] args)
	{
		String s1 = "abc";
		String s2 = new String("abc");
		String s3 = "abc";
		
		//System.out.println("haha");
		System.out.println(s1==s2);
		System.out.println(s1==s3);
		System.out.println(s1.equals(s2));
	}
}

/**
常见功能
(1)获取
① int length()——获取长度
② char charAt(int index)——获取位置上的某个字符
③ int indexOf(int ch——)返回ch在字符串中第一次出现的位置
④ int indexOf(int ch, int fromIndex)——从fromIndex指定位置开始，获取ch在字符串中一次出现的位置。
⑤ int indexOf(String str)——返回的是str在字符串中第一次出现的位置。
⑥ int indexOf(String str, int fromIndex)——从fromIndex指定位置开始，获取str在字符串中出现的位置。
⑦ int lastIndexOf(int ch)——返回指定字符在此字符串中最后一次出现处的索引。
(2)判断
① 字符串中是否包含某一个子串boolean contains(str)
② 字符串中是否有内容boolean isEmpty() 原理就是判断长度是否为0。(1.6产生)
③ 字符串是否是以指定内容开头boolean startsWith(str)
④ 字符串是否是以指定内容结尾boolean endsWith(str)
⑤ 判断字符串内容是否相同。复写了Object类中的equals方法。boolean equals(str)
⑥ 判断内容是否相同，并忽略大小写。boolean equalsIgnoreCase()
(3)转换
① 将字符数组转成字符串
构造函数：String(char[])
		  String(char[],offset,count):将字符数组中的一部分转成字符串。
静态方法：static String copyValueOf(char[]);
		  static String copyValueOf(char[] data, int offset, int count) 
   		  static String valueOf(char[]):
② 将字符串转成字符数组char[] toCharArray()
③ 将字节数组转成字符串
	String(byte[])
	String(byte[],offset,count):将字节数组中的一部分转成字符串。
④ 将字符串转成字节数组byte[]  getBytes()
⑤ 将基本数据类型转成字符串
static String valueOf(int)
	static String valueOf(double)
//3+""(简易方法);//String.valueOf(3);
特殊：字符串和字节数组在转换过程中，是可以指定编码表的。
(4)替换String replace(oldchar,newchar);
(5)切割String[] split(regex);
(6)子串。获取字符串中的一部分。
	String substring(begin);
	String substring(begin,end);
(7)转换，去除空格，比较。
① 将字符串转成大写或则小写。
	String toUpperCase();
	String toLowerCase();
② 将字符串两端的多个空格去除。String trim();
③ 对两个字符串进行自然顺序的比较。int compareTo(string);
String s1 = "a1c";
String s2 = "aaa";
sop(s1.compareTo(s2));——返回-48；1的ascii码是49，a是97。
*/
