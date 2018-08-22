interface Tools {
	public void doSomething();
}

class RunInterface {
	public static void main(String[] args) {
		Tools chuizi = new Tools() {
			@Override
			public void doSomething() {
				System.out.println("榔头砸");
			}
		};

		Tools kuaizi = new Tools() {
			@Override
			public void doSomething() {
				System.out.println("筷子夹");
			}
		};

		chuizi.doSomething();
		kuaizi.doSomething();
	}
}
