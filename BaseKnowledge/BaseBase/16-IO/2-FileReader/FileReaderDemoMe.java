import java.io.*;

class  FileReaderDemoMe
{
	public static void main(String[] args) throws IOException
	{
		FileReader fr = new FileReader("demo.txt");
		
		int chr1 = fr.read();
		System.out.println(chr1);
		int chr2 = fr.read();
		System.out.println(chr2);
		int chr3 = fr.read();
		System.out.println(chr3);
		int chr4 = fr.read();
		System.out.println(chr4);
	}
}