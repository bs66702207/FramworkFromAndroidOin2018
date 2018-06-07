import java.io.*;
class FileDemoMe
{
	public static void main(String[] args) throws IOException
	{
		//consMethod();
		//method_3();
		//method_4();
		method_5();
	}
	
	public static void method_5()
	{
		File f1 = new File("c:\\Test.java");
		File f2 = new File("d:\\hahah.java");

		sop("rename:"+f2.renameTo(f1));

	}
	
	public static void method_4()
	{
		File f = new File("file.txt");
		
		//File f = new File("abc\\file.txt");

		sop("path:"+f.getPath());
		sop("abspath:"+f.getAbsolutePath());
		sop("parent:"+f.getParent());//该方法返回的是绝对路径中的父目录。如果获取的是相对路径，返回null。
									//如果相对路径中有上一层目录那么该目录就是返回结果。
	}
	
	public static void method_3()throws IOException
	{
		//File f = new File("d:\\java1223\\day20\\file2.txt");
		File f = new File("D:\\Fishc\\java_basic_bxd\\code_test\\day20\\file.txt");
		//f.createNewFile();

		f.mkdir();


		//记住在判断文件对象是否是文件或者目录时，必须要先判断该文件对象封装的内容是否存在。
		//通过exists判断。
		sop("dir:"+f.isDirectory());
		sop("file:"+f.isFile());

		sop(f.isAbsolute());
	}
	
	public static void method_2()
	{
		File f = new File("file.txt");
		//File f = new File("FileDemo.java");

		//sop("exists:"+f.exists());

		//sop("execute:"+f.canExecute());

		//创建文件夹
		File dir = new File("abc\\kkk\\a\\a\\dd\\ee\\qq\\aaa");

		sop("mkdir:"+dir.mkdirs());
	}
	
	public static void method_1() throws IOException
	{
		File f = new File("file.txt");
		
		//f.deleteOnExit()
		//code... 即使发生了异常，程序退出时也会删除
		
		
		//create
		//sop("create:"+f.createNewFile());
		
		//delete
		sop("delete:"+f.delete());
	}
	
	public static void consMethod()
	{
		File f1 = new File("a.txt");
		File f2 = new File("c:\\abc","b.txt");
		
		File d = new File("c:\\abc");
		File f3 = new File(d,"c.txt");
		
		sop("f1:"+f1);
		sop("f2:"+f2);
		sop("f3:"+f3);
		
		//File f4 = new File("c:\\abc\\zzz\\a.txt");
		File f4 = new File("c:"+File.separator+"abc"+File.separator+"zzz"+File.separator+"a.txt");
	}
	
	public static void sop(Object obj)
	{
		System.out.println(obj);
	}
}
