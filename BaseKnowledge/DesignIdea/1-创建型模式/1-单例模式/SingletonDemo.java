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
	private volatile static Singletion singleton;
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
public enum Singleton {
	INSTANCE;
	public void doSomeThing() {
	}
}

//反序列化操作提供了readResolve方法, 这个方法可以让开发人员控制对象的反序列化
private Object readResolve() throws ObjectStreamException {
	return singleton;
}
