//1 饿汉模式
public class Singleton {
	private static Singleton instance = new Singleton();
	private Singleton() {
	}
	public static Singleton getInstance() {
		return instance;
	}
}

//2 懒汉模式(线程不安全)
public class Singleton {
	private static Singleton instance;
	private Singleton() {
	}
	public static Singleton getInstance() {
		if(instance == null) {
			instance = new Singleton();
		}
		return instance;
	}
}

//3 懒汉模式(线程安全)
public class Singletion {
	private static Singletion instance;
	private Singletion() {
	}
	public static synchronized Singleton getInstance() {
		if(instance == null) {
			instance = new Singleton();
		}
		return instance;
	}
}

//4 双重检查模式(DCL)
public class Singletion {
	private volatile static Singletion singleton = null;//volatile相当重要，防止指令重排，如果不加的话，有可能A线程还没有构造完毕，B线程就获得了一个非null指针

//用volatile来保证1->2->3的执行顺序，而不是1->3->2
memory =allocate();    //1：分配对象的内存空间 
ctorInstance(memory);  //2：初始化对象 
instance =memory;      //3：设置instance指向刚分配的内存地址

	private Singleton() {
	}
	public static Singleton getInstance() {
		if (instance == null) {
			synchronized (Singleton.class) {
				if (instance == null) {
					instance = new Singletion();
				}
			}
		}
		return singletion;
	}
}

//5 静态内部类单例模式
/*
1.从外部无法访问静态内部类LazyHolder，只有当调用Singleton.getInstance方法的时候，才能得到单例对象INSTANCE。
2.INSTANCE对象初始化的时机并不是在单例类Singleton被加载的时候，而是在调用getInstance方法，使得静态内部类LazyHolder被加载的时候。因此这种实现方式是利用classloader的加载机制来实现懒加载，并保证构建单例的线程安全。
*/
public class Singleton {
	private Singleton() {
	}
	public static Singleton getInstance() {
		return SingletonHolder.sInstance;
	}
	private static class SingletonHolder {
		private static final Singleton sInstance = new Singleton();
	}
}

//6 枚举单例
public enum Singleton {//使用枚举，自带语法糖，JVM会阻止反射获取枚举类的私有构造方法，不过它不是懒加载，而是在枚举类被加载的时候就进行初始化了
	INSTANCE;
	public void doSomeThing() {
	}
}
              线程安全    懒加载    防止反射
双重锁检测      y           y         n
静态内部类      y           y         n
枚举            y           n         y

//反序列化操作提供了readResolve方法, 这个方法可以让开发人员控制对象的反序列化
//如果既想要做到可序列化，又想要反序列化为同一对象，则必须实现readResolve方法
private Object readResolve() throws ObjectStreamException {
	return singleton;
}
