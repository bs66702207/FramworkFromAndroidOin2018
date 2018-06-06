/**
基本数据类型对象包装类
byte	Byte
short	short
int		Integer
long	Long
boolean Boolean
float	Float
double	Double
char	Character

//整数类型的最大值。
sop("int max :"+Integer.MAX_VALUE);

基本数据类型对象包装类的最常见作用，就是用于基本数据类型和字符串类型之间做转换。

(1)基本数据类型转成字符串。应用场景举例：对话窗口里的文本框，输入23(字符串)，软件判断是否大于23时，需要转换成数据类型。
① 基本数据类型+""
② 基本数据类型.toString(基本数据类型值)，如： Integer.toString(34);//将34整数变成"34";

(2)字符串转成基本数据类型。
xxx a = Xxx.parseXxx(String);
int a = Integer.parseInt("123");
double b = Double.parseDouble("12.23");
boolean b = Boolean.parseBoolean("true");
对象调用方式：
Integer i = new Integer("123");
int num = i.intValue();

(3)十进制转成其他进制。
	toBinaryString();
	toHexString();
	toOctalString();

(4)其他进制转成十进制。
	parseInt(string,radix);
*/

class VarAndStringConvert
{
	public static void sop(String str)
	{
		System.out.println(str);
	}
	
	public static void main(String[] args) 
	{
		//整数类型的最大值。
//		sop("int max :"+Integer.MAX_VALUE);
		//int num = Integer.parseInt("123");//必须传入数字格式的字符串。
		//long x = Long.parseLong("123");
		//sop("num="+(num+4));
		
				//sop("num="+(num+4));

		sop(Integer.toBinaryString(-6));
		sop(Integer.toHexString(60));
		int x = Integer.parseInt("3c",16);

		sop("x="+x);
	}
}
