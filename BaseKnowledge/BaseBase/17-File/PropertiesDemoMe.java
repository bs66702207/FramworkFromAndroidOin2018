import java.io.*;
import java.util.*;

class PropertiesDemoMe
{
	public static void main(String[] args) throws IOException
	{
		//setAndGet();
		//method_1();
		loadDemo();
	}
	
	public static void loadDemo() throws IOException
	{
		Properties prop = new Properties();
		FileInputStream fis = new FileInputStream("infome.txt");
		prop.load(fis);
		fis.close();
		prop.setProperty("wangwu", "39");
		
		FileOutputStream fos = new FileOutputStream("infome.txt");
		prop.store(fos,"haha");
		
		//sop(prop);
		prop.list(System.out);
		fos.close();
	} 
	
	public static void method_1() throws IOException
	{
		BufferedReader bufr = new BufferedReader(new FileReader("infome.txt"));
		String line = null;
		Properties prop = new Properties();
		
		while((line=bufr.readLine())!=null)
		{
			String[] arr = line.split("=");
			//sop(line);
			//sop(arr[0]+"....."+arr[1]);
			prop.setProperty(arr[0], arr[1]);
		}
		bufr.close();
		
		sop(prop);
	}
	
	public static void setAndGet()
	{
		Properties prop = new Properties();
		prop.setProperty("zhangsan","30");
		prop.setProperty("lisi","39");
		//System.out.println(prop);
		String value = prop.getProperty("lisi");
		//sop(value);
		prop.setProperty("lisi","89");
		Set<String> names = prop.stringPropertyNames();
		for(String s : names)
		{
			sop(s+":"+prop.getProperty(s));
			return ;
		}
	}
	
	public static void sop(Object obj)
	{
		System.out.println(obj);
	}
}