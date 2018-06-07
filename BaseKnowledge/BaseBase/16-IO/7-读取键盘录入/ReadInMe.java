import java.io.*;
class ReadInMe
{
	public static void main(String[] args) throws IOException
	{
		InputStream in = System.in;
		
		int by = in.read();
		int by1 = in.read();
		int by2 = in.read();
		
		System.out.println(by);
		System.out.println(by1);
		System.out.println(by2);
	}
}