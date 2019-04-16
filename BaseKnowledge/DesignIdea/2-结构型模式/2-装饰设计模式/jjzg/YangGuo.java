//2 组件具体实现类
//被装饰的具体对象，在这里就是被教授武学的具体武侠，也就是杨过。杨过作为武侠当然也会武学(虽然不怎么厉害)
public class YangGuo extends Swordsman {
	@Override
	public void attackMagic() {
		//杨过初始的武学是全真剑法
		System.out.println("杨过使用全真剑法");
	}
}
