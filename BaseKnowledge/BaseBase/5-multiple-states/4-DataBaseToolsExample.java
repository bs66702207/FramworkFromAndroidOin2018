interface UserInfoDao
{
	public abstract void add(User user);
	public abstract void delete(User user);
}
class UserInfoByJDBC implements UserInfoDao
{
	public void add(User user)
	{
		1,JDBC连接数据库
		2,使用sql语句添加数据
		3,关闭连接
	}
	public void delete(User user)
	{
		1,JDBC连接数据库
		2,使用sql语句删除数据
		3,关闭连接
	}
}

class UserInfoByHibernate implements UserInfoDao
{
	public void add(User user)
	{
		1,Hibernate连接数据库
		2,使用sql语句添加数据
		3,关闭连接
	}
	public void delete(User user)
	{
		1,Hibernate连接数据库
		2,使用sql语句删除数据
		3,关闭连接
	}
}

class DataBaseToolsExample
{
	public static void main(String[] args)
	{
		UserInfoDao ui = new UserInfoByJDBC();
		ui.add(user);
		ui.delete(user);
		
		UserInfoDao ui = new UserInfoByHibernate();
		ui.add(user);
		ui.delete(user);
	}
}
