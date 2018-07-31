/*
前面示例实现的CPU接口和CPU实现对象，主板接口和主板实现对象，都不需要变化。
前面示例中创建CPU的简单工厂和创建主板的简单工厂，都不再需要。
新加入的抽象工厂类和实现类：
*/

//public interface AbstractFactory {
interface AbstractFactory {
	/**
	 * 创建CPU对象
	 * @return CPU对象
	 */
	public Cpu createCpu();
	/**
	 * 创建主板对象
	 * @return 主板对象
	 */
	public Mainboard createMainboard();
}

//public class IntelFactory implements AbstractFactory {
class IntelFactory implements AbstractFactory {

	@Override
	public Cpu createCpu() {
		// TODO Auto-generated method stub
		return new IntelCpu(755);
	}

	@Override
	public Mainboard createMainboard() {
		// TODO Auto-generated method stub
		return new IntelMainboard(755);
	}
}

//public class AmdFactory implements AbstractFactory {
class AmdFactory implements AbstractFactory {

	@Override
	public Cpu createCpu() {
		// TODO Auto-generated method stub
		return new IntelCpu(938);
	}

	@Override
	public Mainboard createMainboard() {
		// TODO Auto-generated method stub
		return new IntelMainboard(938);
	}
}

//public class ComputerEngineer {
class ComputerEngineer {
	/**
	 * 定义组装机需要的CPU
	 */
	private Cpu cpu = null;
	/**
	 * 定义组装机需要的主板
	 */
	private Mainboard mainboard = null;
	public void makeComputer(AbstractFactory af) {
		/**
		 * 组装机器的基本步骤
		 */
		//1:首先准备好装机所需要的配件
		prepareHardwares(af);
		//2:组装机器
		//3:测试机器
		//4:交付客户
	}
	private void prepareHardwares(AbstractFactory af) {
		//这里要去准备CPU和主板的具体实现，为了示例简单，这里只准备这两个
		//可是，装机工程师并不知道如何去创建，怎么办呢？

		//直接找相应的工厂获取
		this.cpu = af.createCpu();
		this.mainboard = af.createMainboard();

		//测试配件是否好用
		this.cpu.calculate();
		this.mainboard.installCPU();
	}
}

class AbstractClient {
	public static void main(String[]args) {
		//创建装机工程师对象
		ComputerEngineer cf = new ComputerEngineer();
		//客户选择并创建需要使用的产品对象
		AbstractFactory af = new IntelFactory();
		//告诉装机工程师自己选择的产品，让装机工程师组装电脑
		cf.makeComputer(af);
	}
}
