/**
子继承父，子只能抛出父所能抛出的异常，如果非要有个另类异常，那只能在方法内部try/catch，而绝不能抛，一句话关于异常要遵循父类，额外异常就要自己进行try/catch处理。
多个catch时，父类的catch在后面。
*/

class AException extends Exception
{
	
}

class BException extends AException
{

}

class CException extends Exception
{

}

class Fu
{
	void show() throws AException
	{
		
	}
}

class Test
{
	void function(Fu f)
	{
		try
		{
			f.show();
		}
		catch (AException e)
		{	
		
		}
	}
}

class Zi extends Fu
{
	void show() throws AException// or BException //not CException
	//void show() throws AException, BException, CException// build error
	{
		
	}
}

class ExceptionFuZi
{
	public static void main(String[] args)
	{
		System.out.println("Hello World!");
		Test t = new Test();
		t.function(new Fu());
	}
}
