import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;

//首先创建动态代理类
public class DynamicPurchasing implements InvocationHandler {
	private Object obj;
	public DynamicPurchasing(Object obj) {
		this.obj = obj;
	}

	@Override
	public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
		Object result = method.invoke(obj, args);
		if(method.getName().equals("buy")) {
			System.out.println("Liuwangshu在买买买");
		}
		return result;
	}
}

