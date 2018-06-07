import java.io.*;

class  TransStreamDemoMe2
{
	public static void main(String[] args) throws IOException
	{
		
		//1,
		//BufferedReader bufr = new BufferedReader(new InputStreamReader(System.in));
		//BufferedWriter bufw = new BufferedWriter(new OutputStreamWriter(System.out));
		
		//2,
		//BufferedReader bufr = new BufferedReader(new InputStreamReader(System.in));
		//BufferedWriter bufw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("out.txt")));
		//BufferedWriter bufw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("out.txt"), "GBK"));//GBK默认的
		//BufferedWriter bufw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("out1.txt"), "UTF-8"));//同理，读取转换流传递UTF-8

		//3,
		//BufferedReader bufr = new BufferedReader(new InputStreamReader(new FileInputStream("CopyPic.java")));
		BufferedReader bufr = new BufferedReader(new InputStreamReader(new FileInputStream("out1.txt"), "UTF-8"));
		BufferedWriter bufw = new BufferedWriter(new OutputStreamWriter(System.out));

		
		String line = null;

		while((line=bufr.readLine())!=null)
		{
			if("over".equals(line))
				break;
			bufw.write(line.toUpperCase());
			bufw.newLine();
			bufw.flush();
		}

		bufr.close();

	}
}
