public class Client {
	public static void main(String[] args) {
		//创建杨过
		YangGuo mYangGuo = new YangGuo();
		//洪七公教授杨过打狗棒法，杨过会了打狗棒法
		HongQiGong mHongQiGong = new HongQiGong(mYangGuo);
		mHongQiGong.attackMagic();

		//欧阳锋教授杨过蛤蟆功，杨过学会了蛤蟆功
		OuYangFeng mOuYangFeng = new OuYangFeng(mYangGuo);
		mOuYangFeng.attackMagic();
	}
}
