import java.io.*;

class RandomAccessFileDemoMe 
{
	public static void main(String[] args) throws IOException
	{
		//writeFile();
		//readFile();
		writeFile_2();
	}
	
	public static void writeFile_2()throws IOException
	{
		RandomAccessFile raf = new RandomAccessFile("ran.txt","rw");
		raf.seek(8*3);
		raf.write("周期".getBytes());
		raf.writeInt(103);

		raf.close();
	}
	
	public static void readFile() throws IOException
	{
		RandomAccessFile raf = new RandomAccessFile("ran.txt", "r");
		
		//raf.seek(8);
		
		raf.skipBytes(8);
		
		byte[] buf = new byte[4];
		raf.read(buf);
		String name = new String(buf);
		
		int age = raf.readInt();
		
		sop("name="+name);
		sop("age="+age);
		raf.close();
	}
	
	public static void writeFile() throws IOException
	{
		RandomAccessFile raf = new RandomAccessFile("ran.txt", "rw");
		raf.write("李四".getBytes());
		raf.writeInt(97);
		
		raf.write("王五".getBytes());
		raf.writeInt(99);
		
		raf.close();
	}
	
	public static void sop(Object obj)
	{
		System.out.println(obj);
	}
}
