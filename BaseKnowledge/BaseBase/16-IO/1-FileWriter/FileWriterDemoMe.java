import java.io.*;
class FileWriterDemoMe
{
	public static void main(String[] args) throws IOException
	{
		FileWriter fw = new FileWriter("demo.txt");
		fw.write("abcde");
		//fw.flush();
		fw.write("hahaha");
		//fw.flush();
		fw.close();
	}
}