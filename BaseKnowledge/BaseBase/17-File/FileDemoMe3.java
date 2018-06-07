import java.io.*;

class FileDemoMe3 
{
	public static void main(String[] args) 
	{
		File dir = new File("D:\\Fishc\\java_basic_bxd\\code_test");
		showDir(dir,0);
	}
	
	public static String getLevel(int level)
	{
		StringBuilder sb = new StringBuilder();
		sb.append("|--");
		for(int x=0; x<level; x++)
		{
			//sb.append("|--");
			sb.insert(0,"|  ");

		}
		return sb.toString();
	}
	
	public static void showDir(File dir,int level)
	{
		
		//System.out.println(getLevel(level)+dir.getName());
		System.out.println(getLevel(level)+dir.getAbsolutePath());

		level++;
		File[] files = dir.listFiles();
		for(int x=0; x<files.length; x++)
		{
			if(files[x].isDirectory())
				showDir(files[x],level);
			else
				System.out.println(getLevel(level)+files[x]);
		}
	}
	
}