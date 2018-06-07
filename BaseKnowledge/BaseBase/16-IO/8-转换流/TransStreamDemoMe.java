import java.io.*;
class  TransStreamDemoMe
{
	public static void main(String[] args) throws IOException
	{
		//实现了ReadIn.java的功能，键盘录入、读取
		/*InputStream in = System.in;
		InputStreamReader isr = new InputStreamReader(in);
		BufferedReader bufr = new BufferedReader(isr);
		
		String line = null;
		while((line=bufr.readLine())!=null)
		{
			if("over".equals(line))
				break;
			System.out.println(line.toUpperCase());
		}
		bufr.close();*/
		
		//实现了System.out write方法终端输出
		InputStream in = System.in;
		InputStreamReader isr = new InputStreamReader(in);
		BufferedReader bufr = new BufferedReader(isr);
		
		OutputStream out = System.out;
		OutputStreamWriter osw = new OutputStreamWriter(out);
		BufferedWriter bufw = new BufferedWriter(osw);
	
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
