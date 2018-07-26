//frameworks/base/telephony/java/android/telephony/ServiceState.java

Phone state:
//1.正常操作条件下，电话在家庭网络或漫游中与运营商注册。
public static final int STATE_IN_SERVICE = 0;
//2.电话没有注册到任何运营商，电话当前可以搜索新的运营商注册，或者根本不搜索注册，或者注册被拒绝，或者radio signal不可用。
public static final int STATE_OUT_OF_SERVICE = 1;
//3.电话已注册并锁定。只有紧急号码是允许的。
public static final int STATE_EMERGENCY_ONLY = 2;
//4.Radio of telephony is explicitly powered off
public static final int STATE_POWER_OFF = 3;

Phone scanning:
off:
on:
