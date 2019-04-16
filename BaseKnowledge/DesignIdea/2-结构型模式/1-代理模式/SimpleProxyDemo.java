//我多年没有回过哈尔滨了, 很是想念哈尔滨秋林红肠的味道。
//但是本人工作一直很忙抽不开身, 不能够亲自回哈尔滨购买, 于是就托在哈尔滨的朋友帮我购买秋林红肠。

//1 抽象主题类
//抽象主题类具有真实主题类和代理的共同接口方法, 共同的方法就是购买:
public interface IShop {
	void buy();
}

//2 真实主题类
//这个购买者LiuWangShu也就是我, 实现了IShop接口提供的buy()方法, 如下所示:
public class LiuWangShu implements IShop {
	@Override
	public void buy() {
		System.out.println("购买");
	}
}

//3 代理类
//我找的代理类同样也要实现IShop接口, 并且要持有被代理者, 在buy()方法中调用了被代理者的buy()方法:
public class Purchasing implements IShop {
	private IShop mShop;
	public Purchasing(IShop shop) {
		mShop = shop;
	}
	@Override
	public void buy() {
		mShop.buy();
	}
}

//客户端类
public class Client {
	public static void main(String[] args) {
		IShop LiuWangShu = new LiuWangShu();
		IShop purchasing = new Purchasing(LiuWangShu);
		purchasing.buy();
	}
}

//客户端类的代码就是代理类包含了真实主题类(被代理者), 最终调用的都是真实主题类(被代理者)实现的方法。在上面的例子中就是LiuWangShu类的buy()方法, 所以运行的结果就是“购买”。
