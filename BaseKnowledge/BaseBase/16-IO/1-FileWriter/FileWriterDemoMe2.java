import java.io.*;

class  FileWriterDemoMe2
{
	public static void main(String[] args) 
	{
		FileWriter fw = null;
		try
		{
			fw = new FileWriter("k:\\demo.txt");
			fw.write("abcdefg");
		}
		catch(IOException e)
		{
			System.out.println("catch:"+e.toString());
		}
		finally
		{
			try
			{
				if(fw!=null)
					fw.close();				
			}
			catch (IOException e)
			{
				System.out.println(e.toString());
			}
		}
	}
}