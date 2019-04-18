//具体策略实现
public class CommonRivalStrategy implements FightingStrategy {
	@Override
	public void fighting() {
		System.out.println("遇到了普通的对手，张无忌使用圣火令神功");
	}
}
