/**
	回调函数实际上就是在调用某个函数（通常是API函数）时，将自己的一个函数（这个函数为回调函数）的地址作为参数传递给那个函数。
	而那个函数在需要的时候，利用传递的地址调用回调函数，这时你可以利用这个机会在回调函数中处理消息或完成一定的操作。
	定义三个类，分别是，callback函数的接口类，业务处理，主函数类，在业务处理类中，处理完业务之后，执行一个callback函数。
*/

//callback函数的接口类
interface ComputeCallBack {
	public void onComputeEnd();
}

//业务处理
class TestCallBack {
	public void compute(int n, ComputeCallBack callback) {
		for(int i=0; i<n; i++) {
			System.out.println(i);
		}
		callback.onComputeEnd();
	}
	public void test() {
		System.out.println("Only for test!");
	}
}

//主函数类
class Main {
	public static void main(String[] args) {
		//TestCallBack tcb = new TestCallBack();
		//tcb.test();
		//tcb.compute(1000, new ComputeCallBack() {
		new TestCallBack().compute(1000, new ComputeCallBack() {
			@Override
			public void onComputeEnd() {
				System.out.println("end back!!!");
			}
		});
	}
}
