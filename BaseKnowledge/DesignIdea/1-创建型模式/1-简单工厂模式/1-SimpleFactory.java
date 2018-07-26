//http://www.cnblogs.com/java-my-life/archive/2012/03/28/2418836.html

/**场景问题*/
/*
	举个生活中常见的例子——组装电脑，为讨论使用简单点，只考虑选择CPU和主板的问题。在最终确定这个装机方案之前，还需要整体考虑各个配件之间的兼容性。
比如：CPU和主板，如果使用Intel的CPU和AMD的主板是根本无法组装的。因为Intel的CPU针脚数与AMD主板提供的CPU插口不兼容，就是说如果使用Intel的CPU根本就
插不到AMD的主板中，所以装机方案是整体性的，里面选择的各个配件之间是有关联的。
	对于装机工程师而言，他只知道组装一台电脑，需要相应的配件，但是具体使用什么样的配件，还得由客户说了算。也就是说装机工程师只是负责组装，而客户
负责选择装配所需要的具体配件。因此，当装机工程师为不同的客户组装电脑时，只需要根据客户的装机方案，去获取相应的配件，然后组装即可。
*/

/**使用简单工厂模式的解决方案*/
/*
	考虑客户的功能，需要选择自己需要的CPU和主板，然后告诉装机工程师自己的选择，接下来就等着装机工程师组装电脑了。
　　对装机工程师而言，只是知道CPU和主板的接口，而不知道具体实现，很明显可以用简单工厂模式或工厂方法模式。为了简单，这里选用简单工厂。客户告诉装机
工程师自己的选择，然后装机工程师会通过相应的工厂去获取相应的实例对象。
*/

/**源代码*/
//CPU接口与具体实现
//public interface Cpu {
interface Cpu {
	public void calculate();
}

//public class IntelCpu implements Cpu {
class IntelCpu implements Cpu {
	//CPU的针脚数
	private int pins = 0;
	public IntelCpu(int pins) {
		this.pins = pins;
	}

	@Override
	public void calculate() {
		// TODO Auto-generated method stub
		System.out.println("Intel CPU的针脚数：" + pins);
	}
}

//public class AmdCpu implements Cpu {
class AmdCpu implements Cpu {
	//CPU的针脚数
	private int pins = 0;
	public AmdCpu(int pins) {
		this.pins = pins;
	}

	@Override
	public void calculate() {
		// TODO Auto-generated method stub
		System.out.println("AMD CPU的针脚数：" + pins);
	}
}

//主板接口与具体实现
//public interface Mainboard {
interface Mainboard {
	public void installCPU();
}

//public class IntelMainboard implements Mainboard {
class IntelMainboard implements Mainboard {
	//CPU插槽的孔数
	private int cpuHoles = 0;

	/**
	 * 构造方法，传入CPU插槽的孔数
	 * @param cpuHoles
	 */
	public IntelMainboard(int cpuHoles) {
		this.cpuHoles = cpuHoles;
	}

	@Override
	public void installCPU() {
		// TODO Auto-generated method stub
		System.out.println("Intel主板的CPU插槽孔数是：" + cpuHoles);
	}
}

//public class AmdMainboard implements Mainboard {
class AmdMainboard implements Mainboard {
	//CPU插槽的孔数
	private int cpuHoles = 0;

	/**
	 * 构造方法，传入CPU插槽的孔数
	 * @param cpuHoles
	 */
	public AmdMainboard(int cpuHoles) {
		this.cpuHoles = cpuHoles;
	}

	@Override 
	public void installCPU() {
		// TODO Auto-generated method stub
		System.out.println("AMD主板的CPU插槽孔数是：" + cpuHoles);
	}
}

//CPU与主板工厂类
//public class CpuFactory {
class CpuFactory {
	public static Cpu createCpu(int type) {
		Cpu cpu = null;
		if(type == 1) {
			cpu = new IntelCpu(755);
		} else if(type == 2) {
			cpu = new AmdCpu(938);
		}
		return cpu;
	}
}

//public class MainboardFactory {
class MainboardFactory {
	public static Mainboard createMainboard(int type) {
		Mainboard mainboard = null;
		if(type == 1) {
			mainboard = new IntelMainboard(755);
		} else if(type == 2) {
			mainboard = new AmdMainboard(938);
		}
		return mainboard;
	}
}

//装机工程师类与客户类运行结果如下
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

	public void makeComputer(int cpuType , int mainboard) {
		/**
		 * 组装机器的基本步骤
		 */
		//1:首先准备好装机所需要的配件
		prepareHardwares(cpuType, mainboard);
		//2:组装机器
		//3:测试机器
		//4:交付客户
	}

	private void prepareHardwares(int cpuType , int mainboard) {
		//这里要去准备CPU和主板的具体实现，为了示例简单，这里只准备这两个
		//可是，装机工程师并不知道如何去创建，怎么办呢？

		//直接找相应的工厂获取
		this.cpu = CpuFactory.createCpu(cpuType);
		this.mainboard = MainboardFactory.createMainboard(mainboard);

		//测试配件是否好用
		this.cpu.calculate();
		this.mainboard.installCPU();
	}
}

/*
运行结果:
$ java Client
Intel CPU的针脚数：755
Intel主板的CPU插槽孔数是：755
*/

//public class Client {
class Client {
	public static void main(String[]args) {
		ComputerEngineer cf = new ComputerEngineer();
		cf.makeComputer(1,1);
		cf.makeComputer(1,2);
	}
}

/*
	上面的实现，虽然通过简单工厂方法解决了：对于装机工程师，只知CPU和主板的接口，而不知道具体实现的问题。但还有一个问题没有解决，那就是这些CPU对象和主板对象其实是有关系的，需要相互匹配的。
而上面的实现中，并没有维护这种关联关系，CPU和主板是由客户任意选择，这是有问题的。比如在客户端调用makeComputer时，传入参数为(1,2)，运行结果
Intel CPU的针脚数：755
AMD主板的CPU插槽孔数是：938
	观察上面结果就会看出问题。客户选择的是Intel的CPU针脚数为755，而选择的主板是AMD，主板上的CPU插孔是938，根本无法组装，这就是没有维护配件之间的关系造成的。该怎么解决这个问题呢？
	请看抽象工厂模式2-AbstractFactory.java
*/
