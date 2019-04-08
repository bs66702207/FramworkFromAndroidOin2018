//1.抽象产品类
//我们创建一个计算机的抽象产品类，其有一个抽象方法用于启动计算机
public abstract class Computer {
    /**
     * 产品的抽象方法，由具体的产品类实现
     */
	public abstract void start();
}

//2.具体产品类
//接着我们创建各个品牌的计算机，其都继承了自己的父类Computer，并实现了父类的start方法。具体的计算机产品分别是联想、惠普和华硕计算机:
public class LenovoComputer extends Computer {
	@Override
	public void start() {
		System.out.println("联想电脑启动");
	}
}

public class HpComputer extends Computer {
	@Override
	public void start() {
		System.out.println("惠普电脑启动");
	}
}

public class AsusComputer extends Computer {
	@Override
	public void start() {
		System.out.println("华硕电脑启动");
	}
}

//3. 工厂类
//接下来创建一个工厂类，它提供了一个静态方法createComputer用来生产计算机。你只需要传入自己想生产的计算机的品牌，它就会实例化相应品牌的计算机对象
public class ComputerFactory {
	public static Computer createComputer(String type) {
		Computer mComputer = null;
		switch (type) {
			case "lenovo":
			mComputer = new LenovoComputer();
			break;
		case "hp":
			mComputer = new HpComputer();
			break;
		case "asus":
			mComputer = new AsusComputer();
			break;
		}
		return mComputer;
	}
}

//4. 客户端调用工厂类
//客户端调用工厂类，传入"hp"生产出惠普计算机并调用该计算机对象的start方法
public class CreateComputer {
	public static void main(String[]args) {
		ComputerFactory.createComputer("hp").start();
	}
}

