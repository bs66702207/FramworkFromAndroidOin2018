//装饰者具体实现类-洪七公
public class HongQiGong extends Master {
	public HongQiGong(Swordsman mSwordsman) {
		super(mSwordsman);
	}
	public void teachAttackMagic() {
		System.out.println("洪七公教授打狗棒法");
		System.out.println("杨过使用打狗棒法");
	}
	@Override
	public void attackMagic() {
		super.attackMagic();
		teachAttackMagic();
	}
}
