import java.util.*;
class  EncodeDemoMe
{
	public static void main(String[] args)throws Exception 
	{
		//encode
		String s = "你好";
		byte[] b1 = s.getBytes("GBK");
		//byte[] b1 = s.getBytes("utf-8");
		System.out.println(Arrays.toString(b1));
		
		//decode
		//String s1 = new String(b1,"GBK");
		//String s1 = new String(b1,"ISO8859-1");
		String s1 = new String(b1,"utf-8");
		System.out.println("s1="+s1);
		
		//encode
		//byte[] b2 = s1.getBytes("ISO8859-1");
		byte[] b2 = s1.getBytes("utf-8");
		System.out.println(Arrays.toString(b2));

		//decode
		String s2 = new String(b2,"gbk");
		System.out.println("s2="+s2);
	}
}