//装饰者具体实现类-欧阳锋
public class OuYangFeng extends Master {
	public OuYangFeng(Swordsman mSwordsman) {
		super(mSwordsman);
	}
	public void teachAttackMagic() {
		System.out.println("欧阳锋教授蛤蟆功");
		System.out.println("杨过使用蛤蟆功");
	}
	@Override
	public void attackMagic() {
		super.attackMagic();
		teachAttackMagic();
	}
}
