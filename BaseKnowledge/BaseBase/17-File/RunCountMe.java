import java.io.*;
import java.util.*;

class  RunCountMe
{
	public static void main(String[] args) throws IOException
	{
		Properties prop = new Properties();
		File file = new File("count.ini");
		if(!file.exists())
		{
			file.createNewFile();
		}
		//FileInputStream fis = new FileInputStream("count.properties");
		FileInputStream fis = new FileInputStream(file);
		
		prop.load(fis);
		
		prop.getProperty("time");
		int count = 0;
		String value = prop.getProperty("time");
		
		if(value != null)
		{
			count = Integer.parseInt(value);
			if(count >= 5)
			{
				sop("Hello, used number has done, please pay for it.");
			}
		}
		count++;
		prop.setProperty("time", count+"");
		
		FileOutputStream fos = new FileOutputStream(file);
		prop.store(fos,"time+1");
		fos.close();
		fis.close();
	}
	public static void sop(Object obj)
	{
		System.out.println(obj);
	}
}