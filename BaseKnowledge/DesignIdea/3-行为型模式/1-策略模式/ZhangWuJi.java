public class ZhangWuJi {
	public static void main(String[] args) {
		Context context;
		//张无忌遇到对手宋青书，采用对弱的对手的策略
		context = new Context(new WeakRivalStrategy());
		context.fighting();

		//张无忌遇到对手灭绝师太，采用对普通的对手的策略
		context = new Context(new CommonRivalStrategy());
		context.fighting();

		//张无忌遇到对手成昆，采用对强劲的对手的策略
		context = new Context(new StrongRivalStrategy());
		context.fighting();
	}
}
