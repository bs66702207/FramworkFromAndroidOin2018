//1 创建抽象工厂
//抽象工厂里面有一个createComputer方法，想生产哪个品牌的计算机就生产哪个品牌的，如下所示。
public abstract class ComputerFactory {
	public abstract <T extends Computer> T createComputer(Class<T> clz);//包括T在内的任何T的子类
}

//2 具体工厂
//广大代工厂是一个具体的工厂，其继承抽象工厂，通过反射来生产不同厂家的计算机:
public class GDComputerFactory extends ComputerFactory {
	@Override
	public <T extends Computer> T createComputer(Class<T> clz) {
	Computer computer = null;

	String classname = clz.getName();
	try {
		//通过反射来生产不同厂家的计算机
		computer = (Computer) Class.forName(classname).newInstance();
	} catch (InstantiationException e) {
		e.printStackTrace();
	} catch (IllegalAccessException e) {
		e.printStackTrace();
	} catch (ClassNotFoundException e) {
		e.printStackTrace();
	}
		return (T) computer;
	}
}

//3 客户端调用
//客户端创建了GDComputerFactor,并分别生产了联想、惠普和华硕计算机:



public static void main(String[] args) {
	ComputerFactory computerFactory = new GDComputerFactory();

	LenovoComputer lenovoComputer = computerFactory.createComputer(LenovoComputer.class);
	lenovoComputer.start();

	HpComputer hpComputer = computerFactory.createComputer(HpComputer.class);
	hpComputer.start();

	AsusComputer asusComputer = computerFactory.createComputer(AsusComputer.class);
	asusComputer.start();

}
