//1 创建产品类
//要组装一台电脑(Computer类)，我们假设它有三个部件：CPU 、主板以及内存。在Computer类中提供三个set方法分别设置这三个属性
public class Computer {
	private String mCpu;
	private String mMainboard;
	private String mRam;

	public void setmCpu(String mCpu) {
		this.mCpu = mCpu;
	}

	public void setmMainboard(String mMainboard) {
		this.mMainboard = mMainboard;
	}

	public void setmRam(String mRam) {
		this.mRam = mRam;
	}
}

//2 创建Builder类规范产品的组建
//商家组装计算机有一套组装方法的模板，就是一个抽象的Builder类，其里面提供了安装CPU、主板和内存的方法，以及组装成计算机的create方法
public abstract class Builder {
	public abstract void buildCpu(String cpu);
	public abstract void buildMainboard(String mainboard);
	public abstract void buildRam(String ram);
	public abstract Computer create();
}

//商家实现了抽象的Builder类，MoonComputerBuilder类用于组装计算机
public class MyComputerBuilder extends Builder {
	private Computer mComputer = new Computer();
	@Override
		public void buildCpu(String cpu) {
		mComputer.setmCpu(cpu);
	}
	
	@Override
	public void buildMainboard(String mainboard) {
		mComputer.setmMainboard(mainboard);
	}
	
	@Override
	public void buildRam(String ram) {
		mComputer.setmRam(ram);
	}
	
	@Override
	public Computer create() {
		return mComputer;
	}
}

//3 用导演类来统一组装过程
//商家的导演类用来规范组装计算机的流程规范，先安装主板，再安装CPU，最后安装内存并组装成计算机:
public class Direcror {
	Builder mBuild = null;
		public Direcror(Builder build) {
		this.mBuild = build;
	}
	public Computer CreateComputer(String cpu, String mainboard, String ram) {
		 //规范建造流程，这个顺序是由它定的
		this.mBuild.buildMainboard(mainboard);
		this.mBuild.buildCpu(cpu);
		this.mBuild.buildRam(ram);
		return mBuild.create();
	}
}

//4 客户端调用导演类
//最后商家用导演类组装计算机。我们只需要提供自己想要的CPU、主板和内存就可以了，至于商家怎样组装计算机我们无须知道
public class CreatComputer {
	public static void main(String[] args) {
		Builder mBuilder = new MyComputerBuilder();
		Direcror mDirecror=new Direcror(mBuilder);
		mDirecror.CreateComputer("i7","Intel主板","mRam");//返回Computer实例对象
	}
}



