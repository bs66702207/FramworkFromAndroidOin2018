
import java.io.*;

class EncodeStreamMe 
{
	public static void main(String[] args) throws IOException 
	{
			//writeText();
			readText();
	}

	public static void readText()throws IOException 
	{
		InputStreamReader isr = new InputStreamReader(new FileInputStream("gbkES.txt"),"gbk");
		//InputStreamReader isr = new InputStreamReader(new FileInputStream("utf.txt"),"gbk");

		char[] buf = new char[10];
		int len = isr.read(buf);

		String str = new String(buf,0,len);

		System.out.println(str);

		isr.close();
	}
	public static void writeText()throws IOException 
	{
		OutputStreamWriter osw = new OutputStreamWriter(new FileOutputStream("utf.txt"),"UTF-8");
		//OutputStreamWriter osw = new OutputStreamWriter(new FileOutputStream("gbkES.txt"),"GBK");

		osw.write("你好");

		osw.close();
	}

}
