//某宝商城卖商品，如果每个用户下单都生成商品对象显然会耗费很多资源，如果赶上双11，那恐怖的订单量会生成很多商品对象，
//更何况商城卖的商品种类繁多，这样就极易会产生OOM。因此我们采用享元模式来对商品的创建进行优化。

//1 抽象享元角色
//抽象享元角色是一个商品接口，它定义了showGoodsPrice方法来展示商品的价格:
public interface IGoods {
	public void showGoodsPrice(String version);
}
